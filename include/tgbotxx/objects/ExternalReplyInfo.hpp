#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageOrigin.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/LinkPreviewOptions.hpp>
#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/Document.hpp>
#include <tgbotxx/objects/PaidMediaInfo.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/Sticker.hpp>
#include <tgbotxx/objects/Story.hpp>
#include <tgbotxx/objects/Video.hpp>
#include <tgbotxx/objects/VideoNote.hpp>
#include <tgbotxx/objects/Voice.hpp>
#include <tgbotxx/objects/Checklist.hpp>
#include <tgbotxx/objects/Contact.hpp>
#include <tgbotxx/objects/Dice.hpp>
#include <tgbotxx/objects/Game.hpp>
#include <tgbotxx/objects/Giveaway.hpp>
#include <tgbotxx/objects/GiveawayWinners.hpp>
#include <tgbotxx/objects/Invoice.hpp>
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/Venue.hpp>

namespace tgbotxx {
  /// @brief This object contains information about a message that is being replied to, which may come from another chat or forum topic.
  /// @ref https://core.telegram.org/bots/api#externalreplyinfo
  struct ExternalReplyInfo {
    ExternalReplyInfo() = default;
    explicit ExternalReplyInfo(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Origin of the message replied to by the given message
    Ptr<MessageOrigin> origin;

    /// @brief Optional. Chat the original message belongs to. Available only if the chat is a supergroup or a channel.
    Ptr<Chat> chat;

    /// @brief Optional. Unique message identifier inside the original chat. Available only if the original chat is a supergroup or a channel.
    std::int32_t messageId{};

    /// @brief Optional. Options used for link preview generation for the original message, if it is a text message
    Ptr<LinkPreviewOptions> linkPreviewOptions;

    /// @brief Optional. Message is an animation, information about the animation
    Ptr<Animation> animation;

    /// @brief Optional. Message is an audio file, information about the file
    Ptr<Audio> audio;

    /// @brief Optional. Message is a general file, information about the file
    Ptr<Document> document;

    /// @brief Optional. Message contains paid media; information about the paid media
    Ptr<PaidMediaInfo> paidMedia;

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

    /// @brief Optional. Message is a scheduled giveaway, information about the giveaway
    Ptr<Giveaway> giveaway;

    /// @brief Optional. A giveaway with public winners was completed
    Ptr<GiveawayWinners> giveawayWinners;

    /// @brief Optional. Message is an invoice for a payment, information about the invoice.
    /// @link More about payments » https://core.telegram.org/bots/api#payments @endlink
    Ptr<Invoice> invoice;

    /// @brief Optional. Message is a shared location, information about the location
    Ptr<Location> location;

    /// @brief Optional. Message is a native poll, information about the poll
    Ptr<Poll> poll;

    /// @brief Optional. Message is a venue, information about the venue
    Ptr<Venue> venue;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "origin", origin);
      OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
      OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
      OBJECT_SERIALIZE_FIELD_PTR(json, "link_preview_options", linkPreviewOptions);
      OBJECT_SERIALIZE_FIELD_PTR(json, "animation", animation);
      OBJECT_SERIALIZE_FIELD_PTR(json, "audio", audio);
      OBJECT_SERIALIZE_FIELD_PTR(json, "document", document);
      OBJECT_SERIALIZE_FIELD_PTR(json, "paid_media", paidMedia);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo);
      OBJECT_SERIALIZE_FIELD_PTR(json, "sticker", sticker);
      OBJECT_SERIALIZE_FIELD_PTR(json, "story", story);
      OBJECT_SERIALIZE_FIELD_PTR(json, "video", video);
      OBJECT_SERIALIZE_FIELD_PTR(json, "video_note", videoNote);
      OBJECT_SERIALIZE_FIELD_PTR(json, "voice", voice);
      OBJECT_SERIALIZE_FIELD(json, "has_media_spoiler", hasMediaSpoiler);
      OBJECT_SERIALIZE_FIELD_PTR(json, "checklist", checklist);
      OBJECT_SERIALIZE_FIELD_PTR(json, "contact", contact);
      OBJECT_SERIALIZE_FIELD_PTR(json, "dice", dice);
      OBJECT_SERIALIZE_FIELD_PTR(json, "game", game);
      OBJECT_SERIALIZE_FIELD_PTR(json, "giveaway", giveaway);
      OBJECT_SERIALIZE_FIELD_PTR(json, "giveaway_winners", giveawayWinners);
      OBJECT_SERIALIZE_FIELD_PTR(json, "invoice", invoice);
      OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
      OBJECT_SERIALIZE_FIELD_PTR(json, "poll", poll);
      OBJECT_SERIALIZE_FIELD_PTR(json, "venue", venue);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "origin", origin, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, true);
      OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "link_preview_options", linkPreviewOptions, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "animation", animation, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "audio", audio, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "document", document, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "paid_media", paidMedia, true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sticker", sticker, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "story", story, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "video", video, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "video_note", videoNote, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "voice", voice, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_media_spoiler", hasMediaSpoiler, false, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "checklist", checklist, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "contact", contact, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "dice", dice, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "game", game, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "giveaway_winners", giveawayWinners, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "invoice", invoice, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "poll", poll, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "venue", venue, true);
    }
  };
}