#pragma once
#include <cstdint>
#include "Object.hpp"
#include "User.hpp"
#include "MessageEntity.hpp"
#include "Animation.hpp"

namespace tgbotxx {
    /// @brief This object represents a message.
    /// @ref https://core.telegram.org/bots/api#message
    struct Message : Object {
        /// @brief Unique message identifier inside this chat
        std::int64_t messageId;

        /// @brief Optional. Unique identifier of a message thread to which the message belongs; for supergroups only
        std::int64_t messageThreadId;

        /// @brief Optional. Sender of the message; empty for messages sent to channels. For backward compatibility,
        /// the field contains a fake sender user in non-channel chats, if the message was sent on behalf of a chat.
        Ptr<User> from;

        /// @brief Optional. Sender of the message, sent on behalf of a chat. For example,
        /// the channel itself for channel posts, the supergroup itself for messages from anonymous group administrators,
        /// the linked channel for messages automatically forwarded to the discussion group. For backward compatibility,
        /// the field from contains a fake sender user in non-channel chats, if the message was sent on behalf of a chat.
        // Ptr<Chat> senderChat;

        /// @brief Date the message was sent in Unix time
        std::time_t date;

        /// @brief Conversation the message belongs to
        // Ptr<Chat> chat;

        /// @brief Optional. For forwarded messages, sender of the original message
        Ptr<User> forwardFrom;

        /// @brief For messages forwarded from channels or from anonymous administrators,
        /// information about the original sender chat
        // Ptr<Chat> forwardFromChat;

        /// @brief Optional. For messages forwarded from channels, identifier of the original message in the channel
        std::int64_t forwardFromMessageId;

        /// @brief Optional. For forwarded messages that were originally sent in channels or by an anonymous
        /// chat administrator, signature of the message sender if present
        std::string forwardSignature;

        /// @brief Optional. Sender's name for messages forwarded from users who disallow adding a link to
        /// their account in forwarded messages
        std::string forwardSenderName;

        /// @brief Optional. For forwarded messages, date the original message was sent in Unix time
        std::time_t forwardDate;

        /// @brief Optional. True, if the message is sent to a forum topic
        bool isTopicMessage;

        /// @brief Optional. True, if the message is a channel post that was automatically
        /// forwarded to the connected discussion group
        bool isAutomaticForward;

        /// @brief Optional. For replies, the original message. Note that the Message object in this field
        /// will not contain further reply_to_message fields even if it itself is a reply.
        Ptr<Message> replyToMessage;

        /// @brief Optional. Bot through which the message was sent
        Ptr<User> viaBot;

        /// @brief Optional. Date the message was last edited in Unix time
        std::time_t editDate;

        /// @brief Optional. True, if the message can't be forwarded
        bool hasProtectedContent;

        /// @brief Optional. The unique identifier of a media message group this message belongs to
        std::string mediaGroupId;


        /// @brief Optional. Signature of the post author for messages in channels, or the custom title of
        /// an anonymous group administrator
        std::string authorSignature;

        /// @brief Optional. For text messages, the actual UTF-8 text of the message
        std::string text;

        /// @brief Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text
        std::vector<Ptr<MessageEntity>> entities;

        /// @brief Optional. Message is an animation, information about the animation. For backward compatibility,
        /// when this field is set, the document field will also be set
        Ptr<Animation> animation;
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief
        /// @brief

        // TODO: implement fromJson toJson
        nl::json toJson() const override {
          return nl::json();
        }

        void fromJson(const nl::json &json) override {

        }
    };
}