#pragma once
#include <stdexcept>
#include <string>

namespace tgbotxx {
  /// @brief tgbotxx::Exception
  class Exception : public std::runtime_error {
    public:
      explicit Exception(const std::string& what) : std::runtime_error(what) {}
  };
}