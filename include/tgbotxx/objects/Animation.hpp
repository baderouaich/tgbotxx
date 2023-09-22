#pragma once
#include "Object.hpp"
#include <cstdint>
#include <string>
#include "PhotoSize.hpp"

namespace tgbotxx {
    /// @brief This object represents an animation file (GIF or H.264/MPEG-4 AVC video without sound).
    /// @ref https://core.telegram.org/bots/api#animation
    struct Animation {
        /// @brief Identifier for this file, which can be used to download or reuse the file
        std::string fileId;

        /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
        /// Can't be used to download or reuse the file.
        std::string fileUniqueId;

        /// @brief Video width as defined by sender
        std::int32_t width;

        /// @brief Video height as defined by sender
        std::int32_t height;

        /// @brief Duration of the video in seconds as defined by sender
        std::int32_t duration;

        /// @brief Optional. Animation thumbnail as defined by sender
        Ptr<PhotoSize> thumb;

        /// @brief Optional. Original animation filename as defined by sender
        std::string fileName;

        /// @brief Optional. MIME type of the file as defined by sender
        std::string mimeType;

        /// @brief Optional. File size in bytes.
        /// It can be bigger than 2^31 and some programming languages may have difficulty/silent defects in interpreting it.
        /// But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this value.
        std::int64_t fileSize;

        // TODO: implement fromJson toJson
        nl::json toJson() const {
          return nl::json();
        }

        void fromJson(const nl::json &json) {

        }
    };
}