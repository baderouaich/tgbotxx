#pragma once
#include <tgbotxx/Api.hpp>
#include <tgbotxx/Bot.hpp>
#include <tgbotxx/Exception.hpp>

/// Objects
#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/BotCommandScope.hpp>
#include <tgbotxx/objects/BotDescription.hpp>
#include <tgbotxx/objects/BotName.hpp>
#include <tgbotxx/objects/BotShortDescription.hpp>
#include <tgbotxx/objects/CallbackGame.hpp>
#include <tgbotxx/objects/CallbackQuery.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/ChatAdministratorRights.hpp>
#include <tgbotxx/objects/ChatInviteLink.hpp>
#include <tgbotxx/objects/ChatJoinRequest.hpp>
#include <tgbotxx/objects/ChatLocation.hpp>
#include <tgbotxx/objects/ChatMember.hpp>
#include <tgbotxx/objects/ChatMemberUpdated.hpp>
#include <tgbotxx/objects/ChatPermissions.hpp>
#include <tgbotxx/objects/ChatPhoto.hpp>
#include <tgbotxx/objects/ChatShared.hpp>
#include <tgbotxx/objects/ChosenInlineResult.hpp>
#include <tgbotxx/objects/Contact.hpp>
#include <tgbotxx/objects/Dice.hpp>
#include <tgbotxx/objects/Document.hpp>
#include <tgbotxx/objects/EncryptedCredentials.hpp>
#include <tgbotxx/objects/EncryptedPassportElement.hpp>
#include <tgbotxx/objects/File.hpp>
#include <tgbotxx/objects/ForumTopic.hpp>
#include <tgbotxx/objects/ForumTopicClosed.hpp>
#include <tgbotxx/objects/ForumTopicCreated.hpp>
#include <tgbotxx/objects/ForumTopicEdited.hpp>
#include <tgbotxx/objects/ForumTopicReopened.hpp>
#include <tgbotxx/objects/Game.hpp>
#include <tgbotxx/objects/GeneralForumTopicHidden.hpp>
#include <tgbotxx/objects/GeneralForumTopicUnhidden.hpp>
#include <tgbotxx/objects/IReplyMarkup.hpp>
#include <tgbotxx/objects/InlineKeyboardButton.hpp>
#include <tgbotxx/objects/InlineKeyboardMarkup.hpp>
#include <tgbotxx/objects/InlineQuery.hpp>
#include <tgbotxx/objects/InputMedia.hpp>
#include <tgbotxx/objects/Invoice.hpp>
#include <tgbotxx/objects/KeyboardButton.hpp>
#include <tgbotxx/objects/KeyboardButtonPollType.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestChat.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestUser.hpp>
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/LoginUrl.hpp>
#include <tgbotxx/objects/MaskPosition.hpp>
#include <tgbotxx/objects/MenuButton.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/MessageAutoDeleteTimerChanged.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/MessageId.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/OrderInfo.hpp>
#include <tgbotxx/objects/PassportData.hpp>
#include <tgbotxx/objects/PassportFile.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/PollAnswer.hpp>
#include <tgbotxx/objects/PollOption.hpp>
#include <tgbotxx/objects/PreCheckoutQuery.hpp>
#include <tgbotxx/objects/ProximityAlertTriggered.hpp>
#include <tgbotxx/objects/ReplyKeyboardMarkup.hpp>
#include <tgbotxx/objects/ReplyKeyboardRemove.hpp>
#include <tgbotxx/objects/ShippingAddress.hpp>
#include <tgbotxx/objects/ShippingQuery.hpp>
#include <tgbotxx/objects/Sticker.hpp>
#include <tgbotxx/objects/Story.hpp>
#include <tgbotxx/objects/SuccessfulPayment.hpp>
#include <tgbotxx/objects/SwitchInlineQueryChosenChat.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/UserProfilePhotos.hpp>
#include <tgbotxx/objects/UserShared.hpp>
#include <tgbotxx/objects/Venue.hpp>
#include <tgbotxx/objects/Video.hpp>
#include <tgbotxx/objects/VideoChatEnded.hpp>
#include <tgbotxx/objects/VideoChatParticipantsInvited.hpp>
#include <tgbotxx/objects/VideoChatScheduled.hpp>
#include <tgbotxx/objects/VideoChatStarted.hpp>
#include <tgbotxx/objects/VideoNote.hpp>
#include <tgbotxx/objects/Voice.hpp>
#include <tgbotxx/objects/WebAppData.hpp>
#include <tgbotxx/objects/WebAppInfo.hpp>
#include <tgbotxx/objects/WebhookInfo.hpp>
#include <tgbotxx/objects/WriteAccessAllowed.hpp>

/// Utils
#include <tgbotxx/utils/DateTimeUtils.hpp>
#include <tgbotxx/utils/Ptr.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
