#include "PaidSubscriptionBot.hpp"
#include <cpr/cpr.h>
#include <fstream>
#include <string>

using namespace tgbotxx;

PaidSubscriptionBot::PaidSubscriptionBot(const std::string &token, const std::string &paymentProviderToken)
  : Bot(token), m_paymentProviderToken(paymentProviderToken) {}

void PaidSubscriptionBot::onStart() {
  loadSubscribedUsersIds(); // if bot was stopped from a previous run, load back the subscribed user ids.

  // Register my commands
  Ptr<BotCommand> subscribeCmd(new BotCommand());
  subscribeCmd->command = "/subscribe";
  subscribeCmd->description = "Subscribe now to get Bot services for only 1$!";
  api()->setMyCommands({subscribeCmd});

  std::cout << "Bot " << api()->getMe()->firstName << " Started\n";
}

void PaidSubscriptionBot::onStop() {
  saveSubscribedUsersIds(); // Don't lose subscribed user ids! (will be better to save to a database at runtime), for this example's simplicity, let's use a file for simplicity.

  std::cout << "Bot " << api()->getMe()->firstName << " Stopped\n";
}

void PaidSubscriptionBot::onCommand(const Ptr<Message> &message) {
  if (message->text == "/subscribe") {
    const Ptr<User> &sender = message->from;
    const Ptr<Chat> &chat = message->chat;
    if (isUserAlreadySubscribed(sender->id)) {
      api()->sendMessage(chat->id, "You are already subscribed!");
    } else {
      subscribeNewUser(chat->id, sender);
    }
  }
}


bool PaidSubscriptionBot::isUserAlreadySubscribed(UserId id) {
  return std::any_of(m_subscribers.begin(), m_subscribers.end(), [id](const UserId &uid) {
    return id == uid;
  });
}

void PaidSubscriptionBot::subscribeNewUser(ChatId chatId, tgbotxx::Ptr<User> newUser) {
  // Prepare invoice for new user:
  const std::string title = "Bot Subscription";
  const std::string description = "With only 1$ life time subscription, you will have access to all bot services!";
  const std::string payload =
    "subscribe:" + std::to_string(newUser->id); // we will get this payload back in onPreCheckoutQuery
  const std::string currency = "USD";
  std::vector<Ptr<LabeledPrice>> prices;
  Ptr<LabeledPrice> subscriptionPrice = std::make_shared<LabeledPrice>();
  subscriptionPrice->label = "Subscription Price";
  subscriptionPrice->amount = 300; // = 3$ original price (Price of the product in the smallest units of the currency integer)
  prices.push_back(subscriptionPrice);
  Ptr<LabeledPrice> discountPrice = std::make_shared<LabeledPrice>();
  discountPrice->label = "Discount";
  discountPrice->amount = -200; // = -2$ discount (Price of the product in the smallest units of the currency integer)
  prices.push_back(discountPrice);

  // **Important** Note: if you are testing your bot invoice payment, don't pay using real money, use a testing card provided by Telegram explained in README.md
  try {
    // Send invoice to new user
    api()->sendInvoice(chatId, title, description, payload, m_paymentProviderToken, currency, prices);
  }
  catch (const Exception &e) { // Handle issues accordingly ...
    api()->sendMessage(chatId,
                       "Sorry, an error occurred while sending you an invoice. Please report this issue to the admins and try again later.");
    std::cerr << __func__ << ": " << e.what() << std::endl;
  }
}

void PaidSubscriptionBot::onPreCheckoutQuery(const Ptr<PreCheckoutQuery> &preCheckoutQuery) {
  std::cout << __func__ << ": " << preCheckoutQuery->toJson().dump(2) << std::endl;
  std::string payload = preCheckoutQuery->invoicePayload;
  std::string action = StringUtils::split(payload, ':')[0];
  UserId payerId = std::stoull(StringUtils::split(payload, ':')[1]);

  std::cout << "payload: " << payload << std::endl;
  std::cout << "action: " << action << std::endl;
  std::cout << "payerId: " << payerId << std::endl;

  if (action ==
      "subscribe") { // because we set payload in invoice to "subscribe:USER_ID", you can customize it as you like.
    // here do your logic whether to allow or deny this subscription, let's say we only allow 100 subscribers.
    if (m_subscribers.size() < 100) {
      // Approve payment so user can carry on the payment procedure with the payment provider
      bool paymentApproved = api()->answerPreCheckoutQuery(preCheckoutQuery->id, true);
      if (paymentApproved) {
        std::cout << "Payment approved successfully" << std::endl;
        // Note: payment is approved means user can now proceed to the payment phase, it doesn't mean that the user sent the money.
        // We will receive a successful payment message if the payment is successful, see onPaymentSuccessful()
      } else {
        std::cerr << "Payment did not get approved" << std::endl;
      }
    } else {
      // Deny payment
      api()->answerPreCheckoutQuery(preCheckoutQuery->id, false, "Sorry, maximum subscribers reached!");
    }
  }
}

void PaidSubscriptionBot::saveSubscribedUsersIds() {
  std::ofstream ofs{"subscribers.txt"};
  for (const UserId &id: m_subscribers) {
    ofs << id << std::endl;
  }
  ofs.close();

  std::cout << "Saved " << m_subscribers.size() << " subscribers" << std::endl;
}

void PaidSubscriptionBot::loadSubscribedUsersIds() {
  if (std::ifstream ifs{"subscribers.txt"}) {
    std::string idstr;
    while (std::getline(ifs, idstr)) {
      m_subscribers.push_back(std::stoll(idstr));
    }
    ifs.close();
  }
  std::cout << "Loaded " << m_subscribers.size() << " subscribers" << std::endl;
}

void PaidSubscriptionBot::onLongPollError(const std::string &reason) {
  std::cerr << __func__ << ": " << reason << std::endl;
}

void PaidSubscriptionBot::onAnyMessage(const Ptr<Message> &message) {
  if (message->successfulPayment) {
    // Handle successful payments messages
    this->onSuccessfulPayment(message->successfulPayment);
  }
}

void PaidSubscriptionBot::onSuccessfulPayment(const Ptr<SuccessfulPayment> &successfulPayment) {
  std::string payload = successfulPayment->invoicePayload;
  std::string action = StringUtils::split(payload, ':')[0];
  UserId payerId = std::stoull(StringUtils::split(payload, ':')[1]);
  if (action == "subscribe") {
    m_subscribers.push_back(payerId); // or save subscriber UserId to a database...
    std::cout << "New user subscription complete: userId: " << payerId << std::endl;
  }
}