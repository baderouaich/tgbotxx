#pragma once
#include <ctime>
#include <string>

namespace tgbotxx {
  /// @brief Namespace contains useful Date Time related utility functions.
  namespace DateTimeUtils {
    /// @brief Converts an std::time_t to a string date time with a specific format
    /// @param time std::time_t value to convert
    /// @param format Format of the date to return. Default %Y-%m-%d %H:%M:%S (e.g 2023-10-25 12:55:05)
    /// @returns time as string date time with the specific format
    static std::string toString(const std::time_t& time, const std::string_view& format = "%Y-%m-%d %H:%M:%S") {
      char buffer[64]{};
      std::tm *tm_ = std::localtime(&time);
      std::strftime(buffer, sizeof(buffer), format.data(), tm_);
      return std::string{buffer};
    }

    /// @brief returns current date and time as a string with a specific format
    /// @param format Format of the date to return. Default %Y-%m-%d %H:%M:%S (e.g 2023-10-25 12:55:05)
    /// @returns current date time string
    static std::string currentDateTime(const std::string_view& format = "%Y-%m-%d %H:%M:%S") {
      char buffer[64]{};
      std::time_t now = std::time(nullptr);
      return toString(now);
    }
  }
}
