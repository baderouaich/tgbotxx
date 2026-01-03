#pragma once
#include "MaybeInaccessibleMessage.hpp"


#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/ChatShared.hpp>
#include <tgbotxx/objects/Contact.hpp>
#include <tgbotxx/objects/Dice.hpp>
#include <tgbotxx/objects/Document.hpp>
#include <tgbotxx/objects/ForumTopicClosed.hpp>
#include <tgbotxx/objects/ForumTopicCreated.hpp>
#include <tgbotxx/objects/ForumTopicEdited.hpp>
#include <tgbotxx/objects/ForumTopicReopened.hpp>
#include <tgbotxx/objects/Game.hpp>
#include <tgbotxx/objects/GeneralForumTopicHidden.hpp>
#include <tgbotxx/objects/GeneralForumTopicUnhidden.hpp>
#include <tgbotxx/objects/InlineKeyboardMarkup.hpp>
#include <tgbotxx/objects/Invoice.hpp>
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/MessageAutoDeleteTimerChanged.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PassportData.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/ProximityAlertTriggered.hpp>
#include <tgbotxx/objects/Sticker.hpp>
#include <tgbotxx/objects/Story.hpp>
#include <tgbotxx/objects/SuccessfulPayment.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/UsersShared.hpp>
#include <tgbotxx/objects/Venue.hpp>
#include <tgbotxx/objects/Video.hpp>
#include <tgbotxx/objects/VideoChatEnded.hpp>
#include <tgbotxx/objects/VideoChatParticipantsInvited.hpp>
#include <tgbotxx/objects/VideoChatScheduled.hpp>
#include <tgbotxx/objects/VideoChatStarted.hpp>
#include <tgbotxx/objects/VideoNote.hpp>
#include <tgbotxx/objects/Voice.hpp>
#include <tgbotxx/objects/WebAppData.hpp>
#include <tgbotxx/objects/WriteAccessAllowed.hpp>
#include <tgbotxx/objects/DirectMessagesTopic.hpp>
#include <tgbotxx/objects/MessageOrigin.hpp>
#include <tgbotxx/objects/ExternalReplyInfo.hpp>
#include <tgbotxx/objects/TextQuote.hpp>
#include <tgbotxx/objects/SuggestedPostInfo.hpp>
#include <tgbotxx/objects/RefundedPayment.hpp>
#include <tgbotxx/objects/GiftInfo.hpp>
#include <tgbotxx/objects/UniqueGiftInfo.hpp>
#include <tgbotxx/objects/ChatBoostAdded.hpp>
#include <tgbotxx/objects/ChatBackground.hpp>
#include <tgbotxx/objects/DirectMessagePriceChanged.hpp>
#include <tgbotxx/objects/GiveawayCreated.hpp>
#include <tgbotxx/objects/PaidMessagePriceChanged.hpp>

namespace tgbotxx {
  /// @brief Forward declarations (to avoid circular dependencies)
  /// @note included in src/objects/Message.cpp
  struct Chat;
  struct ChecklistTasksDone;
  struct ChecklistTasksAdded;
  struct GiveawayCompleted;
  struct SuggestedPostApproved;
  struct SuggestedPostApprovalFailed;
  struct SuggestedPostDeclined;
  struct SuggestedPostPaid;
  struct SuggestedPostRefunded;

  /// @brief This object represents a message.
  /// @ref https://core.telegram.org/bots/api#message
  struct Message {
      Message() = default;
      explicit Message(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique message identifier inside this chat
      std::int32_t messageId{};

      /// @brief Optional. Unique identifier of a message thread to which the message belongs; for supergroups only
      std::int32_t messageThreadId{};

      /// @brief Optional. Information about the direct messages chat topic that contains the message
      Ptr<DirectMessagesTopic> directMessagesTopic;

      /// @brief Optional. Sender of the message; empty for messages sent to channels. For backward compatibility,
      /// the field contains a fake sender user in non-channel chats, if the message was sent on behalf of a chat.
      Ptr<User> from;

      /// @brief Optional. Sender of the message, sent on behalf of a chat. For example,
      /// the channel itself for channel posts, the supergroup itself for messages from anonymous group administrators,
      /// the linked channel for messages automatically forwarded to the discussion group. For backward compatibility,
      /// the field from contains a fake sender user in non-channel chats, if the message was sent on behalf of a chat.
      Ptr<Chat> senderChat;

      /// @brief Optional. If the sender of the message boosted the chat, the number of boosts added by the user
      std::int32_t senderBoostCount{};

      /// @brief Optional. The bot that actually sent the message on behalf of the business account. Available only for outgoing messages sent on behalf of the connected business account.
      Ptr<User> senderBusinessBot;

      /// @brief Date the message was sent in Unix time. It is always a positive number, representing a valid date.
      std::time_t date{};

      /// @brief Optional. Unique identifier of the business connection from which the message was received.
      /// If non-empty, the message belongs to a chat of the corresponding business account that is independent
      /// from any potential bot chat which might share the same identifier.
      std::string businessConnectionId;

      /// @brief Conversation the message belongs to
      Ptr<Chat> chat;

      /// @brief Optional. Information about the original message for forwarded messages
      Ptr<MessageOrigin> forwardOrigin;

      /// @brief Optional. True, if the message is sent to a forum topic
      bool isTopicMessage{};

      /// @brief Optional. True, if the message is a channel post that was automatically
      /// forwarded to the connected discussion group
      bool isAutomaticForward{};

      /// @brief Optional. For replies, the original message. Note that the Message object in this field
      /// will not contain further reply_to_message fields even if it itself is a reply.
      Ptr<Message> replyToMessage;

      /// @brief Optional. Information about the message that is being replied to, which may come from another chat or forum topic
      Ptr<ExternalReplyInfo> externalReply;

      /// @brief Optional. For replies that quote part of the original message, the quoted part of the message
      Ptr<TextQuote> quote{};

      /// @brief Optional. For replies to a story, the original story
      Ptr<Story> replyToStory;

      /// @brief Optional. Identifier of the specific checklist task that is being replied to
      std::int32_t replyToChecklistTaskId{};

      /// @brief Optional. Bot through which the message was sent
      Ptr<User> viaBot;

      /// @brief Optional. Date the message was last edited in Unix time
      std::time_t editDate{};

      /// @brief Optional. True, if the message can't be forwarded
      bool hasProtectedContent{};

      /// @brief Optional. True, if the message was sent by an implicit action, for example, as an away or a greeting business message, or as a scheduled message
      bool isFromOffline{};

      /// @brief Optional. True, if the message is a paid post. Note that such posts must not be deleted for 24 hours to receive the payment and can't be edited.
      bool isPaidPost{};

      /// @brief Optional. The unique identifier of a media message group this message belongs to
      std::string mediaGroupId;

      /// @brief Optional. Signature of the post author for messages in channels, or the custom title of
      /// an anonymous group administrator
      std::string authorSignature;

      /// @brief Optional. The number of Telegram Stars that were paid by the sender of the message to send it
      std::int64_t paidStarCount{};

      /// @brief Optional. For text messages, the actual UTF-8 text of the message
      std::string text;

      /// @brief Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text
      std::vector<Ptr<MessageEntity>> entities;

      /// @brief Optional. Options used for link preview generation for the message, if it is a text message and link preview options were changed
      Ptr<LinkPreviewOptions> linkPreviewOptions;

      /// @brief Optional. Information about suggested post parameters if the message is a suggested post in a channel direct messages chat. If the message is an approved or declined suggested post, then it can't be edited.
      Ptr<SuggestedPostInfo> suggestedPostInfo{};

      /// @brief Optional. Unique identifier of the message effect added to the message
      std::string effectId;

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

      /// @brief Optional. True, if the caption must be shown above the message media
      bool showCaptionAboveMedia{};

      /// @brief Optional. True, if the message media is covered by a spoiler animation
      bool hasMediaSpoiler{};

      /// @brief Optional. Message is a checklist
      Ptr<Checklist> checklist;

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
      std::vector<Ptr<PhotoSize>> newChatPhoto;

      /// @brief Optional. Service message: the chat photo was deleted
      bool deleteChatPhoto{};

      /// @brief Optional. Service message: the group has been created
      bool groupChatCreated{};

      /// @brief Optional. Service message: the supergroup has been created. This field can't be received in a message
      /// coming through updates, because bot can't be a member of a supergroup when it is created.
      /// It can only be found in reply_to_message if someone replies to a very first message in a directly created supergroup.
      bool supergroupChatCreated{};

      /// @brief Optional. Service message: the channel has been created. This field can't be received in a message
      /// coming through updates, because bot can't be a member of a channel when it is created.
      /// It can only be found in reply_to_message if someone replies to a very first message in a channel.
      bool channelChatCreated{};

      /// @brief Optional. Service message: auto-delete timer settings changed in the chat
      Ptr<MessageAutoDeleteTimerChanged> messageAutoDeleteTimerChanged;

      /// @brief Optional. The group has been migrated to a supergroup with the specified identifier.
      /// This number may have more than 32 significant bits and some programming languages may have
      /// difficulty/silent defects in interpreting it. But it has at most 52 significant bits,
      /// so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
      std::int64_t migrateToChatId{};

      /// @brief Optional. The supergroup has been migrated from a group with the specified identifier.
      /// This number may have more than 32 significant bits and some programming languages may have
      /// difficulty/silent defects in interpreting it. But it has at most 52 significant bits,
      /// so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
      std::int64_t migrateFromChatId{};

      /// @brief Optional. Specified message was pinned. Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply.
      MaybeInaccessibleMessage pinnedMessage{};

      /// @brief Optional. Message is an invoice for a payment, information about the invoice.
      /// @link More about payments » https://core.telegram.org/bots/api#payments @endlink
      Ptr<Invoice> invoice;

      /// @brief Optional. Message is a service message about a successful payment, information about the payment.
      /// @link More about payments » https://core.telegram.org/bots/api#payments @endlink
      Ptr<SuccessfulPayment> successfulPayment;

      /// @brief Optional. Message is a service message about a refunded payment, information about the payment.
      /// @link More about payments » https://core.telegram.org/bots/api#payments @endlink
      Ptr<RefundedPayment> refundedPayment{};

      /// @brief Optional. Service message: users were shared with the bot
      Ptr<UsersShared> usersShared;

      /// @brief Optional. Service message: a chat was shared with the bot
      Ptr<ChatShared> chatShared;

      /// @brief Optional. Service message: a regular gift was sent or received
      Ptr<GiftInfo> gift{};

      /// @brief Optional. Service message: a unique gift was sent or received
      Ptr<UniqueGiftInfo> uniqueGift{};

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

      /// @brief Optional. Service message: user boosted the chat
      Ptr<ChatBoostAdded> boostAdded{};

      /// @brief Optional. Service message: chat background set
      Ptr<ChatBackground> chatBackgroundSet{};

      /// @brief Optional. Service message: some tasks in a checklist were marked as done or not done
      Ptr<ChecklistTasksDone> checklistTasksDone;

      /// @brief Optional. Service message: tasks were added to a checklist
      Ptr<ChecklistTasksAdded> checklistTasksAdded;

      /// @brief Optional. Service message: the price for paid messages in the corresponding direct messages chat of a channel has changed
      Ptr<DirectMessagePriceChanged> directMessagePriceChanged{};

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

      /// @brief Optional. Service message: a scheduled giveaway was created
      Ptr<GiveawayCreated> giveawayCreated{};

      /// @brief Optional. The message is a scheduled giveaway message
      Ptr<Giveaway> giveaway;

      /// @brief Optional. A giveaway with public winners was completed
      Ptr<GiveawayWinners> giveawayWinners;

      /// @brief Optional. Service message: a giveaway without public winners was completed
      Ptr<GiveawayCompleted> giveawayCompleted{};

      /// @brief Optional. Service message: the price for paid messages has changed in the chat
      Ptr<PaidMessagePriceChanged> paidMessagePriceChanged{};

      /// @brief Optional. Service message: a suggested post was approved
      Ptr<SuggestedPostApproved> suggestedPostApproved{};

      /// @brief Optional. Service message: approval of a suggested post has failed
      Ptr<SuggestedPostApprovalFailed> suggestedPostApprovalFailed{};

      /// @brief Optional. Service message: a suggested post was declined
      Ptr<SuggestedPostDeclined> suggestedPostDeclined{};

      /// @brief Optional. Service message: payment for a suggested post was received
      Ptr<SuggestedPostPaid> suggestedPostPaid{};

      /// @brief Optional. Service message: payment for a suggested post was refunded
      Ptr<SuggestedPostRefunded> suggestedPostRefunded{};

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
      [[nodiscard]] nl::json toJson() const;

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json);
  };
}