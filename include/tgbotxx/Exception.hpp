#pragma once
#include <stdexcept>
#include <string>

namespace tgbotxx {
  class Exception : public std::runtime_error {
  public:
     explicit Exception(const std::string &what) : std::runtime_error(what) {}
  };
}