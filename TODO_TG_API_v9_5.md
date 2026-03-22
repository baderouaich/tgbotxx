# 9.3

### Topics in private chats
- [x] Added the field `has_topics_enabled` to the class `User`, which can be used to determine whether forum topic mode is enabled for the bot in private chats.
- [x] Added the method `sendMessageDraft`, allowing partial messages to be streamed to a user while being generated.
- [x] Supported the fields `message_thread_id` and `is_topic_message` in the class `Message` for messages in private chats with forum topic mode enabled.
- [x] Supported the parameter `message_thread_id` in private chats with topics in the methods `sendMessage`, `sendPhoto`, `sendVideo`, `sendAnimation`, `sendAudio`, `sendDocument`, `sendPaidMedia`, `sendSticker`, `sendVideoNote`, `sendVoice`, `sendLocation`, `sendVenue`, `sendContact`, `sendPoll`, `sendDice`, `sendInvoice`, `sendGame`, `sendMediaGroup`, `copyMessage`, `copyMessages`, `forwardMessage`, and `forwardMessages`.
- [x] Supported the parameter `message_thread_id` in private chats in the method `sendChatAction`.
- [x] Supported the parameter `message_thread_id` in private chats with topics in the methods `editForumTopic`, `deleteForumTopic`, and `unpinAllForumTopicMessages`.
- [x] Added the field `is_name_implicit` to the classes `ForumTopic` and `ForumTopicCreated`.

### Gifts
- [x] Added the methods `getUserGifts` and `getChatGifts`.
- [x] Replaced the field `last_resale_star_count` with the fields `last_resale_currency` and `last_resale_amount` in the class `UniqueGiftInfo`.
- [x] Replaced the parameter `exclude_limited` with the parameters `exclude_limited_upgradable` and `exclude_limited_non_upgradable` in the method `getBusinessAccountGifts`.
- [x] Added the value `"gifted_upgrade"` as a possible value of `UniqueGiftInfo.origin`.
- [x] Added the value `"offer"` as a possible value of `UniqueGiftInfo.origin`.
- [x] Added the field `gift_upgrade_sent` to the class `Message`.
- [x] Added the field `gift_id` to the class `UniqueGift`.
- [x] Added the field `is_from_blockchain` to the class `UniqueGift`.
- [x] Added the parameter `exclude_from_blockchain` in the method `getBusinessAccountGifts`.
- [x] Added the fields `personal_total_count` and `personal_remaining_count` to the class `Gift`.
- [x] Added the field `is_premium` to the classes `Gift` and `UniqueGift`.
- [x] Added the field `is_upgrade_separate` to the classes `GiftInfo` and `OwnedGiftRegular`.
- [x] Added the class `UniqueGiftColors`.
- [x] Added the field `has_colors` to the class `Gift`.
- [x] Added the field `colors` to the class `UniqueGift`.
- [x] Added the class `GiftBackground` and the field `background` to the class `Gift`.
- [x] Added the field `unique_gift_variant_count` to the class `Gift`.
- [x] Added the field `unique_gift_number` to the classes `GiftInfo` and `OwnedGiftRegular`.
- [x] Added the field `gifts_from_channels` to the class `AcceptedGiftTypes`.

### Miscellaneous
- [x] Allowed bots to disable their main username if they have additional active usernames purchased on Fragment.
- [x] Allowed bots to disable the right `can_restrict_members` in channel chats.
- [x] Added the method `repostStory`.
- [x] Added the class `UserRating` and the field `rating` to the class `ChatFullInfo`.
- [x] Increased the maximum price for paid media to 25000 Telegram Stars.
- [x] Added the field `paid_message_star_count` to the class `ChatFullInfo`.
- [x] Added the parameter `message_effect_id` to the methods `forwardMessage` and `copyMessage`.
- [x] Added the field `unique_gift_colors` to the class `ChatFullInfo`.
- [x] Added the field `completed_by_chat` to the class `ChecklistTask`.


# 9.4

### Custom Emoji
- [x] Allowed bots to use custom emoji in messages directly sent by the bot to private, group and supergroup chats if the owner of the bot has a Telegram Premium subscription.

### Topics in Private Chats
- [x] Allowed bots to create topics in private chats using the method `createForumTopic`.
- [x] Allowed bots to prevent users from creating and deleting topics in private chats through a new setting in the @BotFather Mini App.
- [x] Added the field `allows_users_to_create_topics` to the class `User`.

### Button Improvements
- [x] Added the field `icon_custom_emoji_id` to the classes `KeyboardButton` and `InlineKeyboardButton`.
- [x] Added the field `style` to the classes `KeyboardButton` and `InlineKeyboardButton`.

### Chat Ownership
- [x] Added the class `ChatOwnerLeft` and the field `chat_owner_left` to the class `Message`.
- [x] Added the class `ChatOwnerChanged` and the field `chat_owner_changed` to the class `Message`.

### Bot Profile
- [x] Added the methods `setMyProfilePhoto` and `removeMyProfilePhoto`.

### Video Improvements
- [x] Added the class `VideoQuality` and the field `qualities` to the class `Video`.

### Profile Audio
- [x] Added the field `first_profile_audio` to the class `ChatFullInfo`.
- [x] Added the class `UserProfileAudios`.
- [x] Added the method `getUserProfileAudios`.

### Gifts
- [x] Added the field `rarity` to the class `UniqueGiftModel`.
- [x] Added the field `is_burned` to the class `UniqueGift`.


# 9.5

### Message Entities
- [x] Added the `MessageEntity` type `date_time`, allowing bots to show a formatted date and time to the user.

### Draft Messages
- [x] Allowed all bots to use the method `sendMessageDraft`.

### Chat Member Tags
- [x] Added the field `tag` to the classes `ChatMemberMember` and `ChatMemberRestricted`.
- [x] Added the method `setChatMemberTag`.
- [x] Added the field `can_edit_tag` to the classes `ChatMemberRestricted` and `ChatPermissions`.
- [x] Added the field `can_manage_tags` to the classes `ChatMemberAdministrator` and `ChatAdministratorRights`.
- [x] Added the parameter `can_manage_tags` to the method `promoteChatMember`.
- [x] Added the field `sender_tag` to the class `Message`.