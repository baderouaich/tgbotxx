#pragma once
/// Available objects: https://core.telegram.org/bots/api#available-types
#include <type_traits>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/utils/Ptr.hpp>
#include <vector>
namespace nl = nlohmann;

/// @brief Helper macros to de/serialize objects


/// Concatenate tokens
#define TGBOTXX_CAT_IMPL(a, b) a##b
#define TGBOTXX_CAT(a, b) TGBOTXX_CAT_IMPL(a, b)

/// Avoid expanded variable names collisions
#define VAR(x) TGBOTXX_CAT(x, __LINE__)

/// Serialize
#define OBJECT_SERIALIZE_FIELD(json, json_field, field) \
  do {                                                  \
    json[json_field] = field;                           \
  } while (false)

#define OBJECT_SERIALIZE_FIELD_PTR(json, json_field, field) \
  do {                                                      \
    if (field) {                                            \
      json[json_field] = (field)->toJson();                 \
    }                                                       \
  } while (false)

#define OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, json_field, array_field) \
  do {                                                                  \
    auto& arr = json[json_field] = nl::json::array();                   \
    for (const auto& e: array_field)                                    \
      arr.emplace_back(e->toJson());                                    \
  } while (false)

#define OBJECT_SERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, json_field, array_array_field) \
  do {                                                                              \
    auto& root_arr = json[json_field] = nl::json::array();                          \
    for (const auto& array: array_array_field) {                                    \
      nl::json arr = nl::json::array();                                             \
      for (const auto& e: array) {                                                  \
        arr.emplace_back(e->toJson());                                              \
      }                                                                             \
      root_arr.emplace_back(arr);                                                   \
    }                                                                               \
  } while (false)

#define OBJECT_SERIALIZE_FIELD_ENUM(json, enum_name, json_field, field) \
  do {                                                                  \
    json[json_field] = TGBOTXX_CAT(enum_name, ToString)(field);         \
  } while (false)

/// Deserialize
#define OBJECT_DESERIALIZE_FIELD(json, json_field, field, default_value, optional)                  \
  do {                                                                                              \
    if (const auto it = json.find(json_field); it != json.cend()) {                                 \
      try {                                                                                         \
        it->get_to(field);                                                                          \
      } catch (const std::exception& e) {                                                           \
        std::ostringstream err{};                                                                   \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Failed to deserialize \""  \
            << json_field << "\" from json object: " << json.dump(2) << "\nReason: " << e.what();   \
        throw Exception(err.str());                                                                 \
      } catch (...) {                                                                               \
        std::ostringstream err{};                                                                   \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Failed to deserialize \""  \
            << json_field << "\" from json object: " << json.dump(2);                               \
        throw Exception(err.str());                                                                 \
      }                                                                                             \
    } else {                                                                                        \
      if (not(optional)) {                                                                          \
        std::ostringstream err{};                                                                   \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \"" \
            << json_field << "\" from json object: " << json.dump(2);                               \
        throw Exception(err.str());                                                                 \
      }                                                                                             \
      field = default_value;                                                                        \
    }                                                                                               \
  } while (false)

#define OBJECT_DESERIALIZE_FIELD_PTR(json, json_field, field, optional)                                                  \
  do {                                                                                                                   \
    static_assert(!std::is_const_v<decltype(field)>, "OBJECT_DESERIALIZE_FIELD_PTR: 'field' must not be const");         \
    static_assert(std::is_same_v<decltype(optional), bool>, "OBJECT_DESERIALIZE_FIELD_PTR: 'optional' must be boolean"); \
    if (const auto it = json.find(json_field); it != json.cend() and it->is_object() and not it->empty()) {              \
      using T = std::remove_cvref_t<decltype(field)>;                                                                    \
      using E = T::element_type;                                                                                         \
      field = makePtr<E>(*it);                                                                                           \
    } else {                                                                                                             \
      if (not(optional)) {                                                                                               \
        std::ostringstream err{};                                                                                        \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \""                      \
            << json_field << "\" from json object: " << json.dump(2);                                                    \
        throw Exception(err.str());                                                                                      \
      }                                                                                                                  \
      field = nullptr;                                                                                                   \
    }                                                                                                                    \
  } while (false)

#define OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, json_field, array_field, optional)                                                \
  do {                                                                                                                             \
    static_assert(!std::is_const_v<decltype(array_field)>, "OBJECT_DESERIALIZE_FIELD_PTR_ARRAY: 'array_field' must not be const"); \
    static_assert(std::is_same_v<decltype(optional), bool>, "OBJECT_DESERIALIZE_FIELD_PTR_ARRAY: 'optional' must be boolean");     \
    if (const auto it = json.find(json_field); it != json.cend() and it->is_array()) {                                             \
      using T = std::remove_cvref_t<decltype(array_field)::value_type>;                                                            \
      using E = T::element_type;                                                                                                   \
      array_field.clear();                                                                                                         \
      array_field.reserve(it->size());                                                                                             \
      for (const auto& obj: *it) {                                                                                                 \
        array_field.emplace_back(new E(obj));                                                                                      \
      }                                                                                                                            \
    } else {                                                                                                                       \
      if (not(optional)) {                                                                                                         \
        std::ostringstream err{};                                                                                                  \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \""                                \
            << json_field << "\" from json object: " << json.dump(2);                                                              \
        throw Exception(err.str());                                                                                                \
      }                                                                                                                            \
      array_field.clear();                                                                                                         \
    }                                                                                                                              \
  } while (false)


#define OBJECT_DESERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, json_field, array_array_field, optional)                                                      \
  do {                                                                                                                                               \
    static_assert(!std::is_const_v<decltype(array_array_field)>, "OBJECT_DESERIALIZE_FIELD_PTR_ARRAY_ARRAY: 'array_array_field' must not be const"); \
    static_assert(std::is_same_v<decltype(optional), bool>, "OBJECT_DESERIALIZE_FIELD_PTR_ARRAY_ARRAY: 'optional' must be boolean");                 \
    if (const auto it = json.find(json_field); it != json.cend() and it->is_array()) {                                                               \
      using ArrayArray = decltype(array_array_field);                                                                                                \
      using Array = ArrayArray::value_type;         /* e.g vector<vector<int> <- > */                                                                \
      using T = ArrayArray::value_type::value_type; /* e.g vector<vector<int>> <-  */                                                                \
      using E = T::element_type;                                                                                                                     \
      array_array_field.clear();                                                                                                                     \
      array_array_field.reserve(it->size());                                                                                                         \
      for (const auto& array: *it) {                                                                                                                 \
        Array arr;                                                                                                                                   \
        arr.reserve(array.size());                                                                                                                   \
        for (const auto& obj: array) {                                                                                                               \
          arr.emplace_back(new E(obj));                                                                                                              \
        }                                                                                                                                            \
        array_array_field.emplace_back(std::move(arr));                                                                                              \
      }                                                                                                                                              \
    } else {                                                                                                                                         \
      if (not(optional)) {                                                                                                                           \
        std::ostringstream err{};                                                                                                                    \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \""                                                  \
            << json_field << "\" from json object: " << json.dump(2);                                                                                \
        throw Exception(err.str());                                                                                                                  \
      }                                                                                                                                              \
      array_array_field.clear();                                                                                                                     \
    }                                                                                                                                                \
  } while (false)

#define OBJECT_DESERIALIZE_FIELD_ENUM(json, enum_name, json_field, field, default_value, optional)                \
  do {                                                                                                            \
    static_assert(std::is_enum_v<decltype(field)>, "OBJECT_DESERIALIZE_FIELD_ENUM: 'field' must be an enum");     \
    static_assert(!std::is_const_v<decltype(field)>, "OBJECT_DESERIALIZE_FIELD_ENUM: 'field' must not be const"); \
    if (const auto it = json.find(json_field); it != json.cend()) {                                               \
      try {                                                                                                       \
        if (auto opt = TGBOTXX_CAT(StringTo, enum_name)(*it))                                                     \
          field = *opt;                                                                                           \
        else                                                                                                      \
          throw Exception("Could not convert string \"" + it->get<std::string>() + "\" to enum");                 \
      } catch (const std::exception& e) {                                                                         \
        std::ostringstream err{};                                                                                 \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Failed to deserialize \""                \
            << json_field << "\" from json object: " << json.dump(2) << "\nReason: " << e.what();                 \
        throw Exception(err.str());                                                                               \
      } catch (...) {                                                                                             \
        std::ostringstream err{};                                                                                 \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Failed to deserialize \""                \
            << json_field << "\" from json object: " << json.dump(2);                                             \
        throw Exception(err.str());                                                                               \
      }                                                                                                           \
    } else {                                                                                                      \
      if (not(optional)) {                                                                                        \
        std::ostringstream err{};                                                                                 \
        err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \""               \
            << json_field << "\" from json object: " << json.dump(2);                                             \
        throw Exception(err.str());                                                                               \
      }                                                                                                           \
      field = static_cast<enum_name>(default_value);                                                              \
    }                                                                                                             \
  } while (false)
