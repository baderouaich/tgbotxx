#pragma once
#include <algorithm>
#include <random>
#include <span>
#include <sstream>
#include <string>
#include <vector>

namespace tgbotxx {
  /// @brief Namespace contains useful string related utility functions.
  namespace StringUtils {
    /// @brief Form a string from a container with a delimiter
    /// @param con: Container of T elements
    /// @param delim: Text to put between each element T
    /// Example: array = [1,2,3]
    ///          StringUtils::join(array, ",") -> "1,2,3"
    template<typename T, typename D>
    [[nodiscard]] static std::string join(std::span<T> con, const D& delim) {
      std::ostringstream oss{};
      auto it = con.begin();
      if (it == con.end()) {
        return {};
      }
      oss << *it;
      ++it;
      for (; it != con.end(); ++it) {
        oss << delim << *it;
      }
      return oss.str();
    }
    template<typename T, typename D>
    [[nodiscard]] static std::string join(const std::vector<T>& con, const D& delim) {
      return join(std::span{con}, delim);
    }

    /// @brief Split a string by delimiter
    /// @param str: String to split
    /// @param delim: Split by delimiter
    /// @return std::vector of chunks
    [[nodiscard]] static std::vector<std::string> split(const std::string& str, char delim) {
      std::vector<std::string> res;
      std::stringstream ss{str};
      std::string chunk;
      while (std::getline(ss, chunk, delim))
        res.push_back(chunk);
      return res;
    }

    /// @brief Lowercase a string
    /// @param str string to lowercase
    /// @return Lowercase copy of str
    [[nodiscard]] static std::string toLowerCopy(std::string str) {
      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      return str;
    }

    /// @brief Lowercase original string str
    /// @param str string to lowercase
    static void toLower(std::string& str) {
      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    /// @brief Uppercase a string
    /// @param str string to uppercase
    /// @return Uppercase copy of str
    [[nodiscard]] static std::string toUpperCopy(std::string str) {
      std::transform(str.begin(), str.end(), str.begin(), ::toupper);
      return str;
    }

    /// @brief Uppercase original string str
    /// @param str string to uppercase
    static void toUpper(std::string& str) {
      std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }

    /// @brief Left trim a string from start (in place)
    /// @param str: string to trim from the left
    static void ltrim(std::string& str) {
      str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                  return !std::isspace(ch);
                }));
    }

    /// @brief Right trim a string from end (in place)
    /// @param str: string to trim from the right
    static void rtrim(std::string& str) {
      str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                  return !std::isspace(ch);
                }).base(),
                str.end());
    }


    /// @brief Left and right trim a string (from beginning and end) (in place)
    /// @param str: string to trim from the left and right
    static void trim(std::string& str) {
      rtrim(str);
      ltrim(str);
    }

    /// @brief Left trim a string from start (copy)
    /// @param s: string to trim from the left
    /// @returns Copy of left trimmed string
    [[nodiscard]] static std::string ltrimCopy(std::string s) {
      ltrim(s);
      return s;
    }

    /// @brief Right trim a string from end (copy)
    /// @param s: string to trim from the right
    /// @returns Copy of right trimmed string
    [[nodiscard]] static std::string rtrimCopy(std::string s) {
      rtrim(s);
      return s;
    }

    /// @brief Left and Right trim a string from start and end (copy)
    /// @param s: string to trim from the left and right
    /// @returns Copy of trimmed string
    [[nodiscard]] static std::string trimCopy(std::string s) {
      trim(s);
      return s;
    }

    /// @brief Returns true if str starts with prefix
    /// @param str: string to check
    /// @param prefix: prefix to check if str starts with it
    /// @param ignoreCase: Case sensitivity, default: false
    /// @returns true if str starts with prefix
    [[nodiscard]] static bool startsWith(const std::string& str, const std::string& prefix, bool ignoreCase = false) {
      if (str.size() < prefix.size()) return false;
      if (ignoreCase)
        return std::equal(prefix.begin(), prefix.end(), str.begin(),
                          [](char a, char b) { return std::tolower(a) == std::tolower(b); });
      return str.compare(0, prefix.size(), prefix) == 0;
    }

    /// @brief Returns true if str ends with suffix
    /// @param str: string to check
    /// @param suffix: suffix to check if str ends with it
    /// @param ignoreCase: Case sensitivity, default: false
    /// @returns true if str ends with suffix
    [[nodiscard]] static bool endsWith(const std::string& str, const std::string& suffix, bool ignoreCase = false) {
      if (str.size() < suffix.size()) return false;
      if (ignoreCase)
        return std::equal(suffix.begin(), suffix.end(), str.begin() + str.size() - suffix.size(),
                          [](char a, char b) { return std::tolower(a) == std::tolower(b); });
      return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    /// Replaces a token within a string with another string
    /// @param str String that contains tokens to replace
    /// @param search Token to replace
    /// @param replace New value to replace token with
    static void replace(std::string& str, const std::string& search, const std::string& replace) {
      if (search.empty()) return; // Avoid infinite loops
      std::size_t pos{0};
      while ((pos = str.find(search, pos)) != std::string::npos) {
        str.replace(pos, search.length(), replace);
        pos += replace.length();
      }
    }


    /// Replaces a token within a string with another string and return a new copy
    /// @param str String that contains tokens to replace
    /// @param search Token to replace
    /// @param replace New value to replace token with
    /// @return new replaced tokens string
    [[nodiscard]] static std::string replaceCopy(std::string str, const std::string& search, const std::string& replace) {
      if (search.empty()) return str; // Avoid infinite loops
      std::size_t pos{0};
      while ((pos = str.find(search, pos)) != std::string::npos) {
        str.replace(pos, search.length(), replace);
        pos += replace.length();
      }
      return str;
    }

    /// Convert a string to T type
    /// @tparam T desired type
    /// @param str string to convert
    /// @return converted string to T
    template<typename T>
    [[nodiscard]] static T to(const std::string& str) {
      T v{};
      std::istringstream oss{str};
      oss >> v;
      return v;
    }

    /// Returns a random string of length characters
    [[nodiscard]] static std::string random(std::size_t length) {
      static std::random_device seed{};
      static std::default_random_engine engine{seed()};
      static std::uniform_int_distribution<short> choice(0, 2);
      static std::uniform_int_distribution<int> lowercaseAlpha('a', 'z');
      static std::uniform_int_distribution<int> uppercaseAlpha('A', 'Z');
      static std::uniform_int_distribution<int> digits('0', '9');

      std::string str(length, '\000');
      for (char& c: str) {
        switch (choice(engine)) {
          case 0: // a-z
            c = static_cast<char>(lowercaseAlpha(engine));
            break;
          case 1: // A-Z
            c = static_cast<char>(uppercaseAlpha(engine));
            break;
          case 2: // 0-9
            c = static_cast<char>(digits(engine));
            break;
          default:
            break;
        }
      }
      return str;
    }
  };
}