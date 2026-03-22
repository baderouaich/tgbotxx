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
- [ ] Replaced the field `last_resale_star_count` with the fields `last_resale_currency` and `last_resale_amount` in the class `UniqueGiftInfo`.
- [ ] Replaced the parameter `exclude_limited` with the parameters `exclude_limited_upgradable` and `exclude_limited_non_upgradable` in the method `getBusinessAccountGifts`.
- [ ] Added the value `"gifted_upgrade"` as a possible value of `UniqueGiftInfo.origin`.
- [ ] Added the value `"offer"` as a possible value of `UniqueGiftInfo.origin`.
- [ ] Added the field `gift_upgrade_sent` to the class `Message`.
- [ ] Added the field `gift_id` to the class `UniqueGift`.
- [ ] Added the field `is_from_blockchain` to the class `UniqueGift`.
- [ ] Added the parameter `exclude_from_blockchain` in the method `getBusinessAccountGifts`.
- [ ] Added the fields `personal_total_count` and `personal_remaining_count` to the class `Gift`.
- [ ] Added the field `is_premium` to the classes `Gift` and `UniqueGift`.
- [ ] Added the field `is_upgrade_separate` to the classes `GiftInfo` and `OwnedGiftRegular`.
- [ ] Added the class `UniqueGiftColors`.
- [ ] Added the field `has_colors` to the class `Gift`.
- [ ] Added the field `colors` to the class `UniqueGift`.
- [ ] Added the class `GiftBackground` and the field `background` to the class `Gift`.
- [ ] Added the field `unique_gift_variant_count` to the class `Gift`.
- [ ] Added the field `unique_gift_number` to the classes `GiftInfo` and `OwnedGiftRegular`.
- [ ] Added the field `gifts_from_channels` to the class `AcceptedGiftTypes`.

### Miscellaneous
- [ ] Allowed bots to disable their main username if they have additional active usernames purchased on Fragment.
- [ ] Allowed bots to disable the right `can_restrict_members` in channel chats.
- [ ] Added the method `repostStory`.
- [ ] Added the class `UserRating` and the field `rating` to the class `ChatFullInfo`.
- [ ] Increased the maximum price for paid media to 25000 Telegram Stars.
- [ ] Added the field `paid_message_star_count` to the class `ChatFullInfo`.
- [ ] Added the parameter `message_effect_id` to the methods `forwardMessage` and `copyMessage`.
- [ ] Added the field `unique_gift_colors` to the class `ChatFullInfo`.
- [ ] Added the field `completed_by_chat` to the class `ChecklistTask`.


# 9.4

### Custom Emoji
- [ ] Allowed bots to use custom emoji in messages directly sent by the bot to private, group and supergroup chats if the owner of the bot has a Telegram Premium subscription.

### Topics in Private Chats
- [ ] Allowed bots to create topics in private chats using the method `createForumTopic`.
- [ ] Allowed bots to prevent users from creating and deleting topics in private chats through a new setting in the @BotFather Mini App.
- [ ] Added the field `allows_users_to_create_topics` to the class `User`.

### Button Improvements
- [ ] Added the field `icon_custom_emoji_id` to the classes `KeyboardButton` and `InlineKeyboardButton`.
- [ ] Added the field `style` to the classes `KeyboardButton` and `InlineKeyboardButton`.

### Chat Ownership
- [ ] Added the class `ChatOwnerLeft` and the field `chat_owner_left` to the class `Message`.
- [ ] Added the class `ChatOwnerChanged` and the field `chat_owner_changed` to the class `Message`.

### Bot Profile
- [ ] Added the methods `setMyProfilePhoto` and `removeMyProfilePhoto`.

### Video Improvements
- [ ] Added the class `VideoQuality` and the field `qualities` to the class `Video`.

### Profile Audio
- [ ] Added the field `first_profile_audio` to the class `ChatFullInfo`.
- [ ] Added the class `UserProfileAudios`.
- [ ] Added the method `getUserProfileAudios`.

### Gifts
- [ ] Added the field `rarity` to the class `UniqueGiftModel`.
- [ ] Added the field `is_burned` to the class `UniqueGift`.


# 9.5

### Message Entities
- [ ] Added the `MessageEntity` type `date_time`, allowing bots to show a formatted date and time to the user.

### Draft Messages
- [ ] Allowed all bots to use the method `sendMessageDraft`.

### Chat Member Tags
- [ ] Added the field `tag` to the classes `ChatMemberMember` and `ChatMemberRestricted`.
- [ ] Added the method `setChatMemberTag`.
- [ ] Added the field `can_edit_tag` to the classes `ChatMemberRestricted` and `ChatPermissions`.
- [ ] Added the field `can_manage_tags` to the classes `ChatMemberAdministrator` and `ChatAdministratorRights`.
- [ ] Added the parameter `can_manage_tags` to the method `promoteChatMember`.
- [ ] Added the field `sender_tag` to the class `Message`.

### UI
- [ ] Added the field `iconCustomEmojiId` to the class `BottomButton`.