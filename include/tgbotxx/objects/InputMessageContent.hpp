#pragma once
#include <tgbotxx/objects/LabeledPrice.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Base class of all inline query results
  /// This object represents the content of a message to be sent as a result of an inline query. Telegram clients currently support the following 5 types:
  /// - InputTextMessageContent
  /// - InputLocationMessageContent
  /// - InputVenueMessageContent
  /// - InputContactMessageContent
  /// - InputInvoiceMessageContent
  /// @ref https://core.telegram.org/bots/api#inputmessagecontent
  struct InputMessageContent {
      InputMessageContent() = default;
      explicit InputMessageContent(const nl::json& json) {
        _fromJson(json);
      }

      /// @brief Type of this content
      std::string type;


      virtual nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        return json;
      }

      virtual void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
      }

    private:
      void _fromJson(const nl::json& json) {
        fromJson(json);
      }
  };


  /// @brief Represents the content of a text message to be sent as the result of an inline query.
  /// @ref https://core.telegram.org/bots/api#inputtextmessagecontent
  struct InputTextMessageContent : InputMessageContent {
      InputTextMessageContent() {
        InputMessageContent::type = "text";
      }
      explicit InputTextMessageContent(const nl::json& json) : InputMessageContent(json) {
        InputMessageContent::type = "text";
      }

      /// @brief Text of the message to be sent, 1-4096 characters
      std::string messageText;

      /// @brief Optional. Mode for parsing entities in the message text. See formatting options for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in message text, which can be specified instead of parse_mode
      std::vector<Ptr<MessageEntity>> entities;

      /// @brief Optional. Disables link previews for links in the sent message
      bool disableWebPagePreview{};

      nl::json toJson() const override {
        nl::json json = InputMessageContent::toJson();
        OBJECT_SERIALIZE_FIELD(json, "message_text", messageText);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities);
        OBJECT_SERIALIZE_FIELD(json, "disable_web_page_preview", disableWebPagePreview);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InputMessageContent::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "message_text", messageText, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities, true);
        OBJECT_DESERIALIZE_FIELD(json, "disable_web_page_preview", disableWebPagePreview, false, true);
      }
  };


  /// @brief Represents the content of a location message to be sent as the result of an inline query.
  /// @ref https://core.telegram.org/bots/api#inputlocationmessagecontent
  struct InputLocationMessageContent : InputMessageContent {
      InputLocationMessageContent() {
        InputMessageContent::type = "location";
      }
      explicit InputLocationMessageContent(const nl::json& json) : InputMessageContent(json) {
        InputMessageContent::type = "location";
      }

      /// @brief Latitude of the location in degrees
      float latitude{};

      /// @brief Longitude of the location in degrees
      float longitude{};

      /// @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500
      float horizontalAccuracy{};

      /// @brief Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
      std::int32_t heading{};

      /// @brief Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified.
      std::int32_t proximityAlertRadius{};


      nl::json toJson() const override {
        nl::json json = InputMessageContent::toJson();
        OBJECT_SERIALIZE_FIELD(json, "latitude", latitude);
        OBJECT_SERIALIZE_FIELD(json, "longitude", longitude);
        OBJECT_SERIALIZE_FIELD(json, "horizontal_accuracy", horizontalAccuracy);
        OBJECT_SERIALIZE_FIELD(json, "heading", heading);
        OBJECT_SERIALIZE_FIELD(json, "proximity_alert_radius", proximityAlertRadius);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InputMessageContent::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "latitude", latitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "longitude", longitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "horizontal_accuracy", horizontalAccuracy, 0.0f, true);
        OBJECT_DESERIALIZE_FIELD(json, "heading", heading, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "proximity_alert_radius", proximityAlertRadius, 0, true);
      }
  };

  /// @brief Represents the content of a venue message to be sent as the result of an inline query.
  /// @ref https://core.telegram.org/bots/api#inputvenuemessagecontent
  struct InputVenueMessageContent : InputMessageContent {
      InputVenueMessageContent() {
        InputMessageContent::type = "venue";
      }
      explicit InputVenueMessageContent(const nl::json& json) : InputMessageContent(json) {
        InputMessageContent::type = "venue";
      }

      /// @brief Latitude of the venue in degrees
      float latitude{};

      /// @brief Longitude of the venue in degrees
      float longitude{};

      /// @brief Name of the venue
      std::string title;

      /// @brief Address of the venue
      std::string address;

      /// @brief Optional. Foursquare identifier of the venue, if known
      std::string foursquareId;

      /// @brief Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
      std::string foursquareType;

      /// @brief Optional. Google Places identifier of the venue
      std::string googlePlaceId;

      /// @brief Optional. Google Places type of the venue. (See supported types.) https://developers.google.com/places/web-service/supported_types
      std::string googlePlaceType;

      nl::json toJson() const override {
        nl::json json = InputMessageContent::toJson();
        OBJECT_SERIALIZE_FIELD(json, "latitude", latitude);
        OBJECT_SERIALIZE_FIELD(json, "longitude", longitude);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "address", address);
        OBJECT_SERIALIZE_FIELD(json, "foursquare_id", foursquareId);
        OBJECT_SERIALIZE_FIELD(json, "foursquare_type", foursquareType);
        OBJECT_SERIALIZE_FIELD(json, "google_place_id", googlePlaceId);
        OBJECT_SERIALIZE_FIELD(json, "google_place_type", googlePlaceType);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InputMessageContent::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "latitude", latitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "longitude", longitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "address", address, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "foursquare_id", foursquareId, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "foursquare_type", foursquareType, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "google_place_id", googlePlaceId, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "google_place_type", googlePlaceType, "", true);
      }
  };

  /// @brief Represents the content of a contact message to be sent as the result of an inline query.
  /// @ref https://core.telegram.org/bots/api#inputcontactmessagecontent
  struct InputContactMessageContent : InputMessageContent {
      InputContactMessageContent() {
        InputMessageContent::type = "contact";
      }
      explicit InputContactMessageContent(const nl::json& json) : InputMessageContent(json) {
        InputMessageContent::type = "contact";
      }

      /// @brief Contact's phone number
      std::string phoneNumber;

      /// @brief Contact's first name
      std::string firstName;

      /// @brief Optional. Contact's last name
      std::string lastName;

      /// @brief Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes
      /// @link vCard https://en.wikipedia.org/wiki/VCard @endlink
      std::string vcard;

      nl::json toJson() const override {
        nl::json json = InputMessageContent::toJson();
        OBJECT_SERIALIZE_FIELD(json, "phone_number", phoneNumber);
        OBJECT_SERIALIZE_FIELD(json, "first_name", firstName);
        OBJECT_SERIALIZE_FIELD(json, "last_name", lastName);
        OBJECT_SERIALIZE_FIELD(json, "vcard", vcard);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InputMessageContent::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "phone_number", phoneNumber, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "vcard", vcard, "", true);
      }
  };

  /// @brief Represents the content of a invoice message to be sent as the result of an inline query.
  /// @ref https://core.telegram.org/bots/api#inputinvoicemessagecontent
  struct InputInvoiceMessageContent : InputMessageContent {
      InputInvoiceMessageContent() {
        InputMessageContent::type = "invoice";
      }
      explicit InputInvoiceMessageContent(const nl::json& json) : InputMessageContent(json) {
        InputMessageContent::type = "invoice";
      }

      /// @brief Product name, 1-32 characters
      std::string title;

      /// @brief Product description, 1-255 characters
      std::string description;

      /// @brief Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes.
      std::string payload;

      /// @brief Payment provider token, obtained via \@BotFather
      std::string providerToken;

      /// @brief Three-letter ISO 4217 currency code, see more on [currencies](https://core.telegram.org/bots/payments#supported-currencies)
      std::string currency;

      /// @brief Price breakdown, a JSON-serialized list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.)
      std::vector<Ptr<LabeledPrice>> prices;

      /// @brief Optional. The maximum accepted amount for tips in the smallest units of the currency (integer, not float/double).
      /// For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145. See the exp parameter in [currencies.json](https://core.telegram.org/bots/payments/currencies.json),
      /// it shows the number of digits past the decimal point for each currency (2 for the majority of currencies).
      /// Defaults to 0
      std::int32_t maxTipAmount{};

      /// @brief Optional. A JSON-serialized array of suggested amounts of tip in the smallest units of the currency (integer, not float/double).
      /// At most 4 suggested tip amounts can be specified. The suggested tip amounts must be positive, passed in a strictly increased order and must not exceed maxTipAmount.
      std::vector<std::int32_t> suggestedTipAmounts;

      /// @brief Optional. A JSON-serialized object for data about the invoice, which will be shared with the payment provider.
      /// A detailed description of the required fields should be provided by the payment provider.
      std::string providerData;

      /// @brief Optional. URL of the product photo for the invoice. Can be a photo of the goods or a marketing image for a service.
      std::string photoUrl;

      /// @brief Optional. Photo size in bytes
      std::int64_t photoSize{};

      /// @brief Optional. Photo width
      std::int32_t photoWidth{};

      /// @brief Optional. Photo height
      std::int32_t photoHeight{};

      /// @brief Optional. Pass True if you require the user's full name to complete the order
      bool needName{};

      /// @brief Optional. Pass True if you require the user's phone number to complete the order
      bool needPhoneNumber{};

      /// @brief Optional. Pass True if you require the user's email address to complete the order
      bool needEmail{};

      /// @brief Optional. Pass True if you require the user's shipping address to complete the order
      bool needShippingAddress{};

      /// @brief Optional. Pass True if the user's phone number should be sent to provider
      bool sendPhoneNumberToProvider{};

      /// @brief Optional. Pass True if the user's email address should be sent to provider
      bool sendEmailToProvider{};

      /// @brief Optional. Pass True if the final price depends on the shipping method
      bool isFlexible{};

      nl::json toJson() const override {
        nl::json json = InputMessageContent::toJson();
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "payload", payload);
        OBJECT_SERIALIZE_FIELD(json, "provider_token", providerToken);
        OBJECT_SERIALIZE_FIELD(json, "currency", currency);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "prices", prices);
        OBJECT_SERIALIZE_FIELD(json, "max_tip_amount", maxTipAmount);
        OBJECT_SERIALIZE_FIELD(json, "suggested_tip_amounts", suggestedTipAmounts);
        OBJECT_SERIALIZE_FIELD(json, "provider_data", providerData);
        OBJECT_SERIALIZE_FIELD(json, "photo_url", photoUrl);
        OBJECT_SERIALIZE_FIELD(json, "photo_size", photoSize);
        OBJECT_SERIALIZE_FIELD(json, "photo_width", photoWidth);
        OBJECT_SERIALIZE_FIELD(json, "photo_height", photoHeight);
        OBJECT_SERIALIZE_FIELD(json, "need_name", needName);
        OBJECT_SERIALIZE_FIELD(json, "need_phone_number", needPhoneNumber);
        OBJECT_SERIALIZE_FIELD(json, "need_email", needEmail);
        OBJECT_SERIALIZE_FIELD(json, "need_shipping_address", needShippingAddress);
        OBJECT_SERIALIZE_FIELD(json, "send_phone_number_to_provider", sendPhoneNumberToProvider);
        OBJECT_SERIALIZE_FIELD(json, "send_email_to_provider", sendEmailToProvider);
        OBJECT_SERIALIZE_FIELD(json, "is_flexible", isFlexible);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InputMessageContent::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "payload", payload, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "provider_token", providerToken, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "currency", currency, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "prices", prices, false);
        OBJECT_DESERIALIZE_FIELD(json, "max_tip_amount", maxTipAmount, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "suggested_tip_amounts", suggestedTipAmounts, std::vector<std::int32_t>(), true);
        OBJECT_DESERIALIZE_FIELD(json, "provider_data", providerData, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "photo_url", photoUrl, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "photo_size", photoSize, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "photo_width", photoWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "photo_height", photoHeight, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "need_name", needName, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "need_phone_number", needPhoneNumber, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "need_email", needEmail, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "need_shipping_address", needShippingAddress, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "send_phone_number_to_provider", sendPhoneNumberToProvider, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "send_email_to_provider", sendEmailToProvider, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "is_flexible", isFlexible, false, true);
      }
  };
}