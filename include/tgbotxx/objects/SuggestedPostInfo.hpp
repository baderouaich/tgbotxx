#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/SuggestedPostPrice.hpp>

namespace tgbotxx {
  /// @brief Contains information about a suggested post.
  /// @ref https://core.telegram.org/bots/api#suggestedpostinfo
  struct SuggestedPostInfo {
    SuggestedPostInfo() = default;
    explicit SuggestedPostInfo(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Enum of possible types of State.
    enum class State : std::uint8_t {
      Pending = 0,
      Approved,
      Declined
    };
    /// @brief Converts enum State to a string
    static std::optional<std::string> StateToString(const State type) noexcept {
      if (type == State::Pending) return "pending";
      if (type == State::Approved) return "approved";
      if (type == State::Declined) return "declined";
      return std::nullopt;
    }
    /// @brief Converts string to an enum State
    static std::optional<State> StringToState(const std::string& str) noexcept {
      if (str == "pending") return State::Pending;
      if (str == "approved") return State::Approved;
      if (str == "declined") return State::Declined;
      return std::nullopt;
    }
    /// @brief State of the suggested post. Currently, it can be one of “pending”, “approved”, “declined”.
    State state{};

    /// @brief Optional. Proposed price of the post. If the field is omitted, then the post is unpaid.
    Ptr<SuggestedPostPrice> price;

    /// @brief Optional. Proposed send date of the post. If the field is omitted,
    /// then the post can be published at any time within 30 days at the sole discretion
    /// of the user or administrator who approves it.
    std::time_t sendDate{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_ENUM(json, State, "state", state);
      OBJECT_SERIALIZE_FIELD_PTR(json, "price", price);
      OBJECT_SERIALIZE_FIELD(json, "send_date", sendDate);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_ENUM(json, State, "state", state, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "price", price, true);
      OBJECT_DESERIALIZE_FIELD(json, "send_date", sendDate, 0, true);
    }
  };
}