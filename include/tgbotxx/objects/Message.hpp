#pragma once
#include "tgbotxx/objects/PhotoSize.hpp"
#include <cstdint>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/Location.hpp>

namespace tgbotxx {
    /// @brief This object represents a message.
    /// @ref https://core.telegram.org/bots/api#message
    struct Message {
        explicit Message(const nl::json& json) {
          fromJson(json);
        }

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

        /// @brief Optional. Message is an audio file, information about the file
        Ptr<Audio> audio;

        /// @brief Optional. Message is a general file, information about the file
        Ptr<Document> document;

        /// @brief Optional. Message is a photo, available sizes of the photo
        std::vector<Ptr<PhotoSize>> photo;

        /// @brief Optional. Message is a sticker, information about the sticker
        Ptr<Sticker> sticker;

        /// @brief Optional. Message is a forwarded story
        Ptr<Story> story;

        /// @brief Optional. Message is a video, information about the video
        Ptr<Video> video;

        /// @brief Optional. Message is a video note, information about the video message
        Ptr<VideoNote> videoNote;

        /// @brief Optional. Message is a voice message, information about the file
        Ptr<Voice> voice;

        /// @brief Optional. Caption for the animation, audio, document, photo, video or voice
        std::string caption;

        /// @brief Optional. For messages with a caption, special entities like usernames, URLs, bot commands, etc. that appear in the caption
        std::vector<Ptr<MessageEntity>> captionEntities;

        /// @brief Optional. True, if the message media is covered by a spoiler animation
        bool hasMediaSpoiler;

        /// @brief Optional. Message is a shared contact, information about the contact
        Ptr<Contact> contact;

        /// @brief Optional. Message is a dice with random value
        Ptr<Dice> dice;

        /// @brief Optional. Message is a game, information about the game.
        /// @link More about games » https://core.telegram.org/bots/api#games @endlink
        Ptr<Game> game;

        /// @brief Optional. Message is a native poll, information about the poll
        Ptr<Poll> poll;

        /// @brief Optional. Message is a venue, information about the venue. For backward compatibility,
        /// when this field is set, the location field will also be set
        Ptr<Venue> venue;

        /// @brief Optional. Message is a shared location, information about the location
        Ptr<Location> location;

        /// @brief Optional. New members that were added to the group or supergroup and information about them (the bot itself may be one of these members)
        std::vector<Ptr<User>> newChatMembers;

        /// @brief Optional. A member was removed from the group, information about them (this member may be the bot itself)
        Ptr<User> leftChatMember;

        /// @brief Optional. A chat title was changed to this value
        std::string newChatTitle;

        /// @brief Optional. A chat photo was change to this value
        Ptr<PhotoSize> newChatPhoto;

        /// @brief Optional. Service message: the chat photo was deleted
        bool deleteChatPhoto;

        /// @brief Optional. Service message: the group has been created
        bool groupChatCreated;

        /// @brief Optional. Service message: the supergroup has been created. This field can't be received in a message
        /// coming through updates, because bot can't be a member of a supergroup when it is created.
        /// It can only be found in reply_to_message if someone replies to a very first message in a directly created supergroup.
        bool supergroupChatCreated;

        /// @brief Optional. Service message: the channel has been created. This field can't be received in a message
        /// coming through updates, because bot can't be a member of a channel when it is created.
        /// It can only be found in reply_to_message if someone replies to a very first message in a channel.
        bool channelChatCreated;

        /// @brief Optional. Service message: auto-delete timer settings changed in the chat
        Ptr<MessageAutoDeleteTimerChanged> messageAutoDeleteTimerChanged;

        /// @brief Optional. The group has been migrated to a supergroup with the specified identifier.
        /// This number may have more than 32 significant bits and some programming languages may have
        /// difficulty/silent defects in interpreting it. But it has at most 52 significant bits,
        /// so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
        std::int64_t migrateToChatId;

        /// @brief Optional. The supergroup has been migrated from a group with the specified identifier.
        /// This number may have more than 32 significant bits and some programming languages may have
        /// difficulty/silent defects in interpreting it. But it has at most 52 significant bits,
        /// so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
        std::int64_t migrateFromChatId;

        /// @brief Optional. Specified message was pinned. Note that the Message object in this field will not contain further reply_to_message fields even if it is itself a reply.
        Ptr<Message> pinnedMessage;

        /// @brief Optional. Message is an invoice for a payment, information about the invoice.
        /// @link More about payments » https://core.telegram.org/bots/api#payments @endlink
        Ptr<Invoice> invoice;

        /// @brief Optional. Message is a service message about a successful payment, information about the payment.
        /// @link More about payments » https://core.telegram.org/bots/api#payments @endlink
        Ptr<SuccessfulPayment> successfulPayment;

        /// @brief Optional. Service message: a user was shared with the bot
        Ptr<UserShared> userShared;

        /// @brief Optional. Service message: a chat was shared with the bot
        Ptr<ChatShared> chatShared;

        /// @brief Optional. The domain name of the website on which the user has logged in.
        /// @link More about Telegram Login » https://core.telegram.org/widgets/login @endlink
        std::string connectedWebsite;

        /// @brief Optional. Service message: the user allowed the bot to write messages after adding it to the attachment or side menu,
        /// launching a Web App from a link, or accepting an explicit request from a Web App sent by the method requestWriteAccess
        Ptr<WriteAccessAllowed> writeAccessAllowed;

        /// @brief Optional. Telegram Passport data
        Ptr<PassportData> passportData;

        /// @brief Optional. Service message. A user in the chat triggered another user's proximity alert while sharing Live Location.
        Ptr<ProximityAlertTriggered> proximityAlertTriggered;

        /// @brief Optional. Service message: forum topic created
        Ptr<ForumTopicCreated> forumTopicCreated;

        /// @brief Optional. Service message: forum topic edited
        Ptr<ForumTopicEdited> forumTopicEdited;

        /// @brief Optional. Service message: forum topic closed
        Ptr<ForumTopicClosed> forumTopicClosed;

        /// @brief Optional. Service message: forum topic reopened
        Ptr<ForumTopicReopened> forumTopicReopened;

        /// @brief Optional. Service message: the 'General' forum topic hidden
        Ptr<GeneralForumTopicHidden> generalForumTopicHidden;

        /// @brief Optional. Service message: the 'General' forum topic unhidden
        Ptr<GeneralForumTopicUnhidden> generalForumTopicUnhidden;

        /// @brief Optional. Service message: video chat scheduled
        Ptr<VideoChatScheduled> videoChatScheduled;

        /// @brief Optional. Service message: video chat started
        Ptr<VideoChatStarted> videoChatStarted;

        /// @brief Optional. Service message: video chat ended
        Ptr<VideoChatEnded> videoChatEnded;

        /// @brief Optional. Service message: new participants invited to a video chat
        Ptr<VideoChatParticipantsInvited> videoChatParticipantsInvited;

        /// @brief Optional. Service message: data sent by a Web App
        Ptr<WebAppData> webAppData;

        /// @brief Optional. Inline keyboard attached to the message. `login_url` buttons are represented as ordinary `url` buttons.
        Ptr<InlineKeyboardMarkup> replyMarkup;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          /// TODO
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);

          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          //... TODO...
          OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, -1, false);
        }
    };
}