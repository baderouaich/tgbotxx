#pragma once
#include <tgbotxx/tgbotxx.hpp>

class PaidSubscriptionBot : public tgbotxx::Bot {
  using UserId = decltype(tgbotxx::User::id);
  using ChatId = decltype(tgbotxx::Chat::id);

public:
  PaidSubscriptionBot(const std::string &token, const std::string& paymentProviderToken);

private:
  void onStart() override;
  void onCommand(const tgbotxx::Ptr<tgbotxx::Message> &message) override;
  void onAnyMessage(const tgbotxx::Ptr<tgbotxx::Message> &message) override;
  void onStop() override;
  /// Called when a new incoming pre-checkout query is received. Contains full information about checkout
  void onPreCheckoutQuery(const tgbotxx::Ptr<tgbotxx::PreCheckoutQuery> &preCheckoutQuery) override;
  void onLongPollError(const std::string& errorMessage, tgbotxx::ErrorCode errorCode) override;
private:
  bool isUserAlreadySubscribed(UserId id);
  void subscribeNewUser(ChatId chatId, tgbotxx::Ptr<tgbotxx::User> newUser);
  void onSuccessfulPayment(const tgbotxx::Ptr<tgbotxx::SuccessfulPayment>& successfulPayment);
  void saveSubscribedUsersIds();
  void loadSubscribedUsersIds();

private:
  std::string m_paymentProviderToken; // tip: better get from ENV on production
  std::vector<UserId> m_subscribers; // tip: better use a realtime database to store subscribers info
};