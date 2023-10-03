
#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace tgbotxx {
  /// @brief Namespace contains useful string related utility functions.
  namespace StringUtils {
    /// @brief Form a string from a container with a delimiter
    /// @example: array = [1,2,3]
    ///           StringUtils::join(array, ",") -> "1,2,3"
    /// @param con: Container of T elements
    /// @param delim: Text to put between each element T
    template<typename T>
    static std::string join(const std::vector<T>& con, const std::string& delim) {
      std::ostringstream oss{};
      for (std::size_t i = 0; i < con.size(); ++i) {
        oss << con[i];
        if (i != con.size() - 1) {
          oss << delim;
        }
      }
      return oss.str();
    }

    /// @brief Split a string by delimiter
    /// @param str: String to split
    /// @param delim: Split by delimiter
    /// @return std::vector of chunks
    static std::vector<std::string> split(const std::string& str, char delim) {
      std::vector<std::string> res;
      std::stringstream ss{str};
      std::string chunk;
      while (std::getline(ss, chunk, delim))
        res.push_back(chunk);
      return res;
    }

    /// @brief Lowercase a string
    /// @param str string to lowercase
    /// @return lowercase version of str
    static std::string toLower(std::string str) {
      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      return str;
    }

    /// @brief Uppercase a string
    /// @param str string to uppercase
    /// @return uppercase version of str
    static std::string toUpper(std::string str) {
      std::transform(str.begin(), str.end(), str.begin(), ::toupper);
      return str;
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
    /// @param str: string to trim from the left
    /// @returns Copy of left trimmed string
    static std::string ltrimCopy(std::string s) {
      ltrim(s);
      return s;
    }

    /// @brief Right trim a string from end (copy)
    /// @param str: string to trim from the right
    /// @returns Copy of right trimmed string
    static std::string rtrimCopy(std::string s) {
      rtrim(s);
      return s;
    }

    /// @brief Left and Right trim a string from start and end (copy)
    /// @param str: string to trim from the left and right
    /// @returns Copy of trimmed string
    static std::string trimCopy(std::string s) {
      trim(s);
      return s;
    }

    /// @brief Returns true if str starts with prefix
    /// @param str: string to check
    /// @param prefix: prefix to check if str starts with it
    /// @param ignoreCase: Case sensitivity, default: false
    /// @returns true if str starts with prefix
    static bool startsWith(const std::string& str, const std::string& prefix, bool ignoreCase = false) {
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
    static bool endsWith(const std::string& str, const std::string& suffix, bool ignoreCase = false) {
      if (str.size() < suffix.size()) return false;
      if (ignoreCase)
        return std::equal(suffix.begin(), suffix.end(), str.begin() + str.size() - suffix.size(),
                          [](char a, char b) { return std::tolower(a) == std::tolower(b); });
      return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
  };
}