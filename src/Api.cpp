#include <tgbotxx/Api.hpp>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/BotCommandScope.hpp>
#include <utility>
#include <cpr/cpr.h>
using namespace tgbotxx;

Api::Api(const std::string& token) : m_token(std::move(token)) {

}



nl::json Api::sendRequest(const std::string& endpoint, const cpr::Multipart& data) const {
  std::ostringstream url{};
  url << BASE_URL << "/bot" << m_token << '/' << endpoint; // workaround: token should have a prefix botTOKEN. see https://stackoverflow.com/a/41460083

  cpr::Header headers =  {
          {"Connection", "close"} // disable keep-alive
  };

  bool isMultipart = not data.parts.empty();
  if(isMultipart) // we have files?
    headers.insert({"Content-Type", "multipart/form-data"});
  else
    headers.insert({"Content-Type", "application/x-www-form-urlencoded"});

  cpr::Response res{};
  if(isMultipart)
    res = cpr::Post(cpr::Url{url.str()}, headers, data, CONNECT_TIMEOUT, TIMEOUT);
  else
    res = cpr::Get(cpr::Url{url.str()}, headers, data, CONNECT_TIMEOUT, TIMEOUT);

  if(!res.text.compare(0, 6, "<html>")) {
    throw Exception("Failed to get a JSON response from Telegram API. Did you enter the correct bot token?");
  }

  try {
    nl::json result = nl::json::parse(res.text);
    if (result["ok"].get<bool>())
      return result["result"];
    else
      throw Exception(result["description"]);
  } catch (const nl::json::exception& e) {
    throw Exception("Failed to parse JSON response: " + res.text + "\nreason: " + e.what());
  } catch(const Exception& e) {
    throw; // rethrow e
  } catch(const std::exception& e) {
    throw; // rethrow e
  }
}

bool Api::deleteWebhook(bool dropPendingUpdates) const {
  cpr::Multipart data{};
  if(dropPendingUpdates)
    data.parts.emplace_back("drop_pending_updates", dropPendingUpdates);
  return sendRequest("deleteWebhook", data).get<bool>();
}

/// Called every LONG_POOL_TIMEOUT seconds
std::vector<Ptr<Update>> Api::getUpdates(std::int32_t offset, std::int32_t limit, std::int32_t timeout, const std::vector<std::string> &allowedUpdates) const {
  cpr::Multipart data = {
          {"offset", offset},
          {"limit", std::max(1, std::min(100, limit))},
          {"timeout", timeout},
          {"allowed_updates", allowedUpdates.empty() ? "[]" : nl::json{allowedUpdates}.dump()},
  };
  nl::json updatesJson = sendRequest("getUpdates", data);
  std::vector<Ptr<Update>> updates;
  updates.reserve(updatesJson.size());
  for(const nl::json& updateObj : updatesJson) {
    Ptr<Update> update(new Update(updateObj));
    updates.push_back(std::move(update));
  }
  return updates;
}

bool Api::setMyCommands(const std::vector<Ptr<BotCommand>> &commands, const Ptr<BotCommandScope>& scope, const std::string &languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(3);

  nl::json commandsJson = nl::json::array();
  for(const Ptr<BotCommand>& command : commands)
      commandsJson.push_back(command->toJson());
  data.parts.emplace_back("commands", commandsJson.dump());
  if (scope) {
    data.parts.emplace_back("scope", scope->toJson().dump());
  }
  if (not languageCode.empty()) {
    data.parts.emplace_back("language_code", languageCode);
  }

  return sendRequest("setMyCommands", data).get<bool>();
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
  if(commandsJson.empty()) return commands;
  commands.reserve(commandsJson.size());
  for(const nl::json& commandObj : commandsJson) {
    Ptr<BotCommand> cmd(new BotCommand(commandObj));
    commands.push_back(std::move(cmd));
  }
  return commands;
}
