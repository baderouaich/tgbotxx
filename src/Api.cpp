#include <tgbotxx/Api.hpp>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
#include <utility>
using namespace tgbotxx;

Api::Api(const std::string &token) : m_token(token) {
    m_session.SetTimeout(TIMEOUT);
    m_session.SetConnectTimeout(CONNECT_TIMEOUT);
    m_session.SetHeader(cpr::Header{
            {"Connection",   "close"}, // disable keep-alive
            {"Accept",       "application/json"},
            {"Content-Type", "application/x-www-form-urlencoded"},
    });
}

nl::json Api::sendRequest(const std::string &endpoint, const cpr::Multipart &data) const {
    std::ostringstream url{};
    url << BASE_URL << "/bot" << m_token << '/'
        << endpoint; // workaround: token should have a prefix botTOKEN. see https://stackoverflow.com/a/41460083
    m_session.SetUrl(cpr::Url{url.str()});
    m_session.SetMultipart(data);

    bool isMultipart = not data.parts.empty();
    if (isMultipart) // we have files?
    {
        m_session.UpdateHeader(cpr::Header{{
                                                   {"Content-Type", "multipart/form-data"}
                                           }});

    } else {
        m_session.UpdateHeader(cpr::Header{{
                                                   {"Content-Type", "application/x-www-form-urlencoded"}
                                           }});
    }

    cpr::Response res{};
    if (isMultipart)
        res = m_session.Post();
    else
        res = m_session.Get();

    if (!res.text.compare(0, 6, "<html>")) {
        throw Exception("Failed to get a JSON response from Telegram API. Did you enter the correct bot token?");
    }

    try {
        nl::json response = nl::json::parse(res.text);
        if (response["ok"].get<bool>()) {
            return response["result"];
        } else {
            std::string desc = response["description"];
            if (response["error_code"] == cpr::status::HTTP_NOT_FOUND) {
                desc += ". Did you enter the correct bot token?";
            }
            throw Exception(desc);
        }
    } catch (const nl::json::exception &e) {
        throw Exception("Failed to parse JSON response: " + res.text + "\nreason: " + e.what());
    } catch (const Exception &e) {
        throw; // rethrow e
    } catch (const std::exception &e) {
        throw; // rethrow e
    }
}

Ptr<User> Api::getMe() const {
    nl::json json = sendRequest("getMe");
    Ptr<User> me(new User(json));
    return me;
}

bool Api::deleteWebhook(bool dropPendingUpdates) const {
    cpr::Multipart data{};
    if (dropPendingUpdates)
        data.parts.emplace_back("drop_pending_updates", dropPendingUpdates);
    return sendRequest("deleteWebhook", data);
}

/// Called every LONG_POOL_TIMEOUT seconds
std::vector<Ptr<Update>> Api::getUpdates(std::int32_t offset, std::int32_t limit, std::int32_t timeout,
                                         const std::vector<std::string> &allowedUpdates) const {
    cpr::Multipart data = {
            {"offset",          offset},
            {"limit",           std::max(1, std::min(100, limit))},
            {"timeout",         timeout},
            {"allowed_updates", allowedUpdates.empty() ? "[]" : nl::json{allowedUpdates}.dump()},
    };
    nl::json updatesJson = sendRequest("getUpdates", data);
    std::vector<Ptr<Update>> updates;
    updates.reserve(updatesJson.size());
    for (const nl::json &updateObj: updatesJson) {
        Ptr<Update> update(new Update(updateObj));
        updates.push_back(std::move(update));
    }
    return updates;
}

bool Api::setMyCommands(const std::vector<Ptr<BotCommand>> &commands, const Ptr<BotCommandScope> &scope,
                        const std::string &languageCode) const {
    cpr::Multipart data{};
    data.parts.reserve(3);

    nl::json commandsJson = nl::json::array();
    for (const Ptr<BotCommand> &command: commands)
        commandsJson.push_back(command->toJson());
    data.parts.emplace_back("commands", commandsJson.dump());
    if (scope) {
        data.parts.emplace_back("scope", scope->toJson().dump());
    }
    if (not languageCode.empty()) {
        data.parts.emplace_back("language_code", languageCode);
    }

    return sendRequest("setMyCommands", data);
}

std::vector<Ptr<BotCommand>> Api::getMyCommands(const Ptr<BotCommandScope> &scope, const std::string &languageCode) const {
    std::vector<Ptr<BotCommand>> commands;
    cpr::Multipart data{};
    data.parts.reserve(2);
    if (scope) {
        data.parts.emplace_back("scope", scope->toJson().dump());
    }
    if (not languageCode.empty()) {
        data.parts.emplace_back("language_code", languageCode);
    }
    nl::json commandsJson = sendRequest("getMyCommands", data);
    if (commandsJson.empty()) return commands;
    commands.reserve(commandsJson.size());
    for (const nl::json &commandObj: commandsJson) {
        Ptr<BotCommand> cmd(new BotCommand(commandObj));
        commands.push_back(std::move(cmd));
    }
    return commands;
}

bool Api::logOut() const {
    return sendRequest("logOut");
}

bool Api::close() const {
    return sendRequest("close");
}

Ptr<Message> Api::sendMessage(const std::int64_t& chatId, const std::string &text,
                              bool disableWebPagePreview, std::int64_t replyToMessageId, const Ptr<IReplyMarkup>& replyMarkup,
                              const std::string &parseMode, bool disableNotification,
                              const std::vector<Ptr<MessageEntity>>& entities, bool allowSendingWithoutReply,
                              bool protectContent, std::int64_t messageThreadId) const {
    cpr::Multipart data{};
    data.parts.reserve(10);
    data.parts.emplace_back("chat_id", std::to_string(chatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
    data.parts.emplace_back("text", text);
    if (disableWebPagePreview)
        data.parts.emplace_back("disable_web_page_preview", disableWebPagePreview);
    if (replyToMessageId)
        data.parts.emplace_back("reply_to_message_id", replyToMessageId);
    if (replyMarkup)
        data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
    if (not parseMode.empty())
        data.parts.emplace_back("parse_mode", parseMode);
    if (disableNotification)
        data.parts.emplace_back("disable_notification", disableNotification);
    if (not entities.empty()) {
        nl::json entitiesArray = nl::json::array();
        for(const Ptr<MessageEntity>& entity : entities)
            entitiesArray.push_back(entity->toJson());
        data.parts.emplace_back("entities", entitiesArray.dump());
    }
    if (allowSendingWithoutReply)
        data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
    if (protectContent)
        data.parts.emplace_back("protect_content", protectContent);
    if (messageThreadId)
        data.parts.emplace_back("message_thread_id", messageThreadId);

     nl::json sentMessageObj = sendRequest("sendMessage", data);
     Ptr<Message> message(new Message(sentMessageObj));
     return message;
}