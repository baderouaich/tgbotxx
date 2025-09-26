#pragma once
#include <cpr/status_codes.h>
#include <stdexcept>
#include <string>

namespace tgbotxx {
  /// @ref https://core.telegram.org/api/errors
  enum class ErrorCode : std::int32_t {
    /// Other error codes non Telegram Api related (such as https requests failures, json parsing errors..)
    /// More information will be provided with Exception message
    OTHER = 0,

    /// The request must be repeated, but directed to a different data center.
    SEE_OTHER = cpr::status::HTTP_SEE_OTHER,

    /// The query contains errors. In the event that a request was created using a form and contains user generated data,
    /// the user should be notified that the data must be corrected before the query is repeated.
    BAD_REQUEST = cpr::status::HTTP_BAD_REQUEST,

    /// There was an unauthorized attempt to use functionality available only to authorized users.
    UNAUTHORIZED = cpr::status::HTTP_UNAUTHORIZED,

    /// Privacy violation. For example, an attempt to write a message to someone who has blacklisted the current user.
    FORBIDDEN = cpr::status::HTTP_FORBIDDEN,

    /// An attempt to invoke a non-existent object, such as a method.
    NOT_FOUND = cpr::status::HTTP_NOT_FOUND,

    /// Similar to 400 BAD_REQUEST, but the app must display the error to the user a bit differently.
    NOT_ACCEPTABLE = cpr::status::HTTP_NOT_ACCEPTABLE,

    /// The maximum allowed number of attempts to invoke the given method with the given input parameters has been exceeded.
    /// For example, in an attempt to request a large number of text messages (SMS) for the same phone number.
    /// Error Example: FLOOD_WAIT_X: A wait of X seconds is required (where X is a number)
    FLOOD = 420,

    /// Conflict: terminated by other long poll or webhook
    CONFLICT = cpr::status::HTTP_CONFLICT,

    /// Too Many Requests: retry after X
    TOO_MANY_REQUESTS = cpr::status::HTTP_TOO_MANY_REQUESTS,

    /// Bad Gateway
    BAD_GATEWAY = cpr::status::HTTP_BAD_GATEWAY,

    /// An internal server error occurred while a request was being processed; for example,
    /// there was a disruption while accessing a database or file storage.
    /// If a client receives a 500 error, or you believe this error should not have occurred,
    /// please collect as much information as possible about the query and error and send it to the developers.
    INTERNAL = cpr::status::HTTP_INTERNAL_SERVER_ERROR
  };
  static std::ostream& operator<<(std::ostream& os, const ErrorCode& errorCode) noexcept {
     switch (errorCode) {
       case ErrorCode::OTHER: return os << "OTHER";
       case ErrorCode::SEE_OTHER: return os << "SEE_OTHER";
       case ErrorCode::BAD_REQUEST: return os << "BAD_REQUEST";
       case ErrorCode::UNAUTHORIZED: return os << "UNAUTHORIZED";
       case ErrorCode::FORBIDDEN: return os << "FORBIDDEN";
       case ErrorCode::NOT_FOUND: return os << "NOT_FOUND";
       case ErrorCode::NOT_ACCEPTABLE: return os << "NOT_ACCEPTABLE";
       case ErrorCode::FLOOD: return os << "FLOOD";
       case ErrorCode::CONFLICT: return os << "CONFLICT";
       case ErrorCode::TOO_MANY_REQUESTS: return os << "TOO_MANY_REQUESTS";
       case ErrorCode::BAD_GATEWAY: return os << "BAD_GATEWAY";
       case ErrorCode::INTERNAL: return os << "INTERNAL";
       default: return os << "Unknown ErrorCode (" << static_cast<std::int32_t>(errorCode) << ')';
     }
  }

  static bool isErrorCode(const std::int32_t c) noexcept {
    switch (c) {
      case static_cast<std::int32_t>(ErrorCode::OTHER):
      case static_cast<std::int32_t>(ErrorCode::SEE_OTHER):
      case static_cast<std::int32_t>(ErrorCode::BAD_REQUEST):
      case static_cast<std::int32_t>(ErrorCode::UNAUTHORIZED):
      case static_cast<std::int32_t>(ErrorCode::FORBIDDEN):
      case static_cast<std::int32_t>(ErrorCode::NOT_FOUND):
      case static_cast<std::int32_t>(ErrorCode::NOT_ACCEPTABLE):
      case static_cast<std::int32_t>(ErrorCode::FLOOD):
      case static_cast<std::int32_t>(ErrorCode::CONFLICT):
      case static_cast<std::int32_t>(ErrorCode::TOO_MANY_REQUESTS):
      case static_cast<std::int32_t>(ErrorCode::BAD_GATEWAY):
      case static_cast<std::int32_t>(ErrorCode::INTERNAL):
        return true;
      default:
        return false;
    }
  }

  /// @brief tgbotxx::Exception
  class Exception : public std::runtime_error {
      const ErrorCode m_errorCode; ///<! Telegram Api response error_code

    public:
      explicit Exception(const std::string& errMessage) : std::runtime_error(errMessage), m_errorCode(ErrorCode::OTHER) {}
      explicit Exception(const std::string& errMessage, ErrorCode errCode) : std::runtime_error(errMessage), m_errorCode(errCode) {}

      [[nodiscard]] ErrorCode errorCode() const noexcept {
        return m_errorCode;
      }
  };
}