#pragma once
#include <cstdint>
#include <string>
#include "Object.hpp"

namespace tgbotxx {
    /// @brief This object represents one size of a photo or a file / sticker thumbnail.
    /// @ref https://core.telegram.org/bots/api#photosize
    struct PhotoSize {
      /// @brief Identifier for this file, which can be used to download or reuse the file
      std::string fileId;

      /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
      /// Can't be used to download or reuse the file.
      std::string fileUniqueId;

      /// @brief Photo width
      std::int32_t width;

      /// @brief Photo height
      std::int32_t height;

      /// @brief Optional. File size in bytes
      std::int64_t fileSize;

      // TODO: implement fromJson toJson
      nl::json toJson() const {
        return nl::json();
      }

      void fromJson(const nl::json &json) {

      }
    };
}