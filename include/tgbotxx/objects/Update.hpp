#pragma once
#include "Object.hpp"
#include <nlohmann/json.hpp>
namespace nl = nlohmann;

namespace tgbotxx {
    struct Message;
    /// @brief This object represents an incoming update.
    /// At most one of the optional parameters can be present in any given update.
    /// @ref https://core.telegram.org/bots/api#update
    struct Update : Object {
        explicit Update(const nl::json& json) {
          fromJson(json);
        }



        /// @brief The update's unique identifier.
        /// Update identifiers start from a certain positive number and increase sequentially.
        /// This ID becomes especially handy if you're using webhooks, since it allows you to ignore repeated updates
        /// or to restore the correct update sequence, should they get out of order.
        /// If there are no new updates for at least a week, then identifier of the next update will be chosen randomly
        /// instead of sequentially.
        std::uint64_t update_id;

        /// @brief Optional. New incoming message of any kind — text, photo, sticker, etc.
        Ptr<Message> message;

        /// @brief Optional. New version of a message that is known to the bot and was edited
        Ptr<Message> editedMessage;

        /// @brief Optional. New incoming channel post of any kind — text, photo, sticker, etc.
        Ptr<Message> channelPost;

        /// @brief Optional. New version of a channel post that is known to the bot and was edited
        Ptr<Message> editedChannelPost;

        // TODO: complete members: https://core.telegram.org/bots/api#update
        // TODO: implement fromJson toJson
        nl::json toJson() const override {
          return nl::json();
        }

        void fromJson(const nl::json &json) override {

        }
    };
}