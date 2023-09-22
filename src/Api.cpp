#include <tgbotxx/Api.hpp>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <cpr/cpr.h>
using namespace tgbotxx;

Api::Api(const std::string& token) : m_token(token) {

}



nl::json Api::sendRequest(const std::string& endpoint, const cpr::Multipart& data) const {
  std::ostringstream url{};
  url << BASE_URL << "/bot" << m_token << '/' << endpoint; // workaround: token should have a prefix botTOKEN. see https://stackoverflow.com/a/41460083
  std::cout << url.str() << std::endl;

  cpr::Header headers =  {
          {"Connection", "close"} // disable keep-alive
  };

  bool isMultipart = not data.parts.empty();
  if(isMultipart) // we have files?
    headers.insert({"Content-Type", "multipart/form-data"});
  else
    headers.insert({"Content-Type", "application/x-www-form-urlencoded"});

  cpr::Response res{};
  if(isMultipart)
    res = cpr::Post(cpr::Url{url.str()}, headers, data, CONNECT_TIMEOUT, TIMEOUT);
  else
    res = cpr::Get(cpr::Url{url.str()}, headers, data, CONNECT_TIMEOUT, TIMEOUT);

#ifndef NDEBUG
  std::cout << res.text << std::endl;
#endif

  if(!res.text.compare(0, 6, "<html>")) {
    throw Exception("Failed to get a JSON response from Telegram API. Did you pass the correct bot token?");
  }

  try {
    nl::json result = nl::json::parse(res.text);
    if (result["ok"].get<bool>())
      return result["result"];
    else
      throw Exception(result["description"]);
  } catch(const Exception& e){
    throw; // rethrow e
  } catch (const nl::json::exception& e) {
    throw Exception("Failed to parse JSON response: " + res.text + "\nreason: " + e.what());
  }
}

bool Api::deleteWebhook(bool dropPendingUpdates) const {
  cpr::Multipart data{};
  if(dropPendingUpdates)
    data.parts.emplace_back("dropPendingUpdates", dropPendingUpdates);
  nl::json res = sendRequest("deleteWebhook", data);
  std::cout << __func__ << ": " << res.dump(2) << std::endl;
  return res.get<bool>();
}

std::vector<Ptr<Update>> Api::getUpdates() const {
  cpr::Multipart data = { // TODO
          {"offset", ""},
          {"limit", ""},
          {"timeout", ""},
          {"allowed_updates", ""},
  };
  nl::json updatesJson = sendRequest("getUpdates", data);
  std::vector<Ptr<Update>> updates;
  updates.reserve(updatesJson.size());
  for(const nl::json& updateObj : updatesJson){
    //Ptr<Update> update(new Update(updateObj));
    //updates.push_back(std::move(update));
  }
  return updates;
}