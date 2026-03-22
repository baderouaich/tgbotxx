#pragma once
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace tgbotxx {
  /// @brief Namespace contains useful Date Time related utility functions.
  namespace DateTimeUtils {
    /// @brief Converts an std::time_t to a string date time with a specific format
    /// @param time std::time_t value to convert
    /// @param format Format of the date to return. Default %Y-%m-%d %H:%M:%S (e.g 2023-10-25 12:55:05) https://www.gnu.org/software/libc/manual/html_node/Formatting-Calendar-Time.html
    /// @returns on success: time as string datetime with the specific format
    ///          on failure: empty std::string
    [[nodiscard]] static std::string toString(const std::time_t& time, const std::string_view& format = "%Y-%m-%d %H:%M:%S") {
      std::tm tm_{};

#ifdef _WIN32
      localtime_s(&tm_, &time);
#else
      localtime_r(&time, &tm_);
#endif

      std::string result(128, '\0');
      const std::size_t size = std::strftime(result.data(), result.size(), format.data(), &tm_);
      if (size == 0) return {};

      result.resize(size);
      return result;
    }

    /// @brief Converts a string date time with a specific format to an std::time_t
    /// @param dateTimeStr String date time to convert
    /// @param format Format of the string date to return. Default %Y-%m-%d %H:%M:%S (e.g 2023-10-25 12:55:05) https://www.gnu.org/software/libc/manual/html_node/Formatting-Calendar-Time.html
    /// @returns non-negative std::time_t on success
    [[nodiscard]] static std::time_t fromString(const std::string& dateTimeStr, const std::string_view& format = "%Y-%m-%d %H:%M:%S") {
      std::tm tm{};
      std::istringstream iss{dateTimeStr};

      if (!(iss >> std::get_time(&tm, format.data()))) {
        return -1; // failed to parse dateTimeStr
      }

      tm.tm_isdst = -1;
      return std::mktime(&tm);
    }

    /// @brief returns current date and time as a string with a specific format
    /// @param format Format of the date to return. Default %Y-%m-%d %H:%M:%S (e.g 2023-10-25 12:55:05) https://www.gnu.org/software/libc/manual/html_node/Formatting-Calendar-Time.html
    /// @returns current date time string
    [[nodiscard]] static std::string now(const std::string_view& format = "%Y-%m-%d %H:%M:%S") {
      const std::time_t tm = std::time(nullptr);
      return toString(tm, format);
    }

    [[deprecated("Use DateTimeUtils::now() instead")]] [[nodiscard]] static std::string currentDateTime(const std::string_view& format = "%Y-%m-%d %H:%M:%S") {
      return now(format);
    }

  }
}
