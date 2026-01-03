#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/LocationAddress.hpp>
#include <tgbotxx/objects/ReactionType.hpp>
#include <string>

namespace tgbotxx {

  /// @brief Base class for types of clickable areas on a story
  /// @ref https://core.telegram.org/bots/api#storyareatype
  struct StoryAreaType {
    StoryAreaType() = default;
    explicit StoryAreaType(const nl::json& json) {
      StoryAreaType::fromJson(json);
    }
    virtual ~StoryAreaType() = default;

    /// @brief Type of the area
    std::string type;

    [[nodiscard]] virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief Story area pointing to a location
  struct StoryAreaTypeLocation : StoryAreaType {
    StoryAreaTypeLocation() {
      type = "location";
    }
    explicit StoryAreaTypeLocation(const nl::json& json) {
      StoryAreaTypeLocation::fromJson(json);
    }

    float latitude{};
    float longitude{};
    Ptr<LocationAddress> address;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = StoryAreaType::toJson();
      OBJECT_SERIALIZE_FIELD(json, "latitude", latitude);
      OBJECT_SERIALIZE_FIELD(json, "longitude", longitude);
      OBJECT_SERIALIZE_FIELD_PTR(json, "address", address);
      return json;
    }

    void fromJson(const nl::json& json) override {
      StoryAreaType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "latitude", latitude, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "longitude", longitude, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "address", address, true);
    }
  };

  /// @brief Story area pointing to a suggested reaction
  struct StoryAreaTypeSuggestedReaction : StoryAreaType {
    StoryAreaTypeSuggestedReaction() {
      type = "suggested_reaction";
    }
    explicit StoryAreaTypeSuggestedReaction(const nl::json& json) {
      StoryAreaTypeSuggestedReaction::fromJson(json);
    }

    Ptr<ReactionType> reactionType;
    bool isDark{};
    bool isFlipped{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = StoryAreaType::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "reaction_type", reactionType);
      OBJECT_SERIALIZE_FIELD(json, "is_dark", isDark);
      OBJECT_SERIALIZE_FIELD(json, "is_flipped", isFlipped);
      return json;
    }

    void fromJson(const nl::json& json) override {
      StoryAreaType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "reaction_type", reactionType, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_dark", isDark, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_flipped", isFlipped, false, true);
    }
  };

  /// @brief Story area pointing to a link
  struct StoryAreaTypeLink : StoryAreaType {
    StoryAreaTypeLink() {
      type = "link";
    }
    explicit StoryAreaTypeLink(const nl::json& json) {
      StoryAreaTypeLink::fromJson(json);
    }

    std::string url;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = StoryAreaType::toJson();
      OBJECT_SERIALIZE_FIELD(json, "url", url);
      return json;
    }

    void fromJson(const nl::json& json) override {
      StoryAreaType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "url", url, "", false);
    }
  };

  /// @brief Story area showing weather information
  struct StoryAreaTypeWeather : StoryAreaType {
    StoryAreaTypeWeather() {
      type = "weather";
    }
    explicit StoryAreaTypeWeather(const nl::json& json) {
      StoryAreaTypeWeather::fromJson(json);
    }

    float temperature{};
    std::string emoji;
    std::int32_t backgroundColor{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = StoryAreaType::toJson();
      OBJECT_SERIALIZE_FIELD(json, "temperature", temperature);
      OBJECT_SERIALIZE_FIELD(json, "emoji", emoji);
      OBJECT_SERIALIZE_FIELD(json, "background_color", backgroundColor);
      return json;
    }

    void fromJson(const nl::json& json) override {
      StoryAreaType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "temperature", temperature, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "emoji", emoji, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "background_color", backgroundColor, 0, false);
    }
  };

  /// @brief Story area pointing to a unique gift
  struct StoryAreaTypeUniqueGift : StoryAreaType {
    StoryAreaTypeUniqueGift() {
      type = "unique_gift";
    }
    explicit StoryAreaTypeUniqueGift(const nl::json& json) {
      StoryAreaTypeUniqueGift::fromJson(json);
    }

    std::string name;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = StoryAreaType::toJson();
      OBJECT_SERIALIZE_FIELD(json, "name", name);
      return json;
    }

    void fromJson(const nl::json& json) override {
      StoryAreaType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
    }
  };

}
