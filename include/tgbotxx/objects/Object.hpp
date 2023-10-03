#pragma once
/// Available objects: https://core.telegram.org/bots/api#available-types
#include <cstdint>
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

/// Serialize
#define OBJECT_SERIALIZE_FIELD(json, json_field, field) \
  json[json_field] = field;

#define OBJECT_SERIALIZE_FIELD_PTR(json, json_field, field, default_value) \
  json[json_field] = field ? field->toJson() : default_value

#define OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, json_field, array_field) \
  json[json_field] = nl::json::array();                                 \
  for (const auto& e: array_field)                                      \
    json[json_field].push_back(e->toJson());

#define OBJECT_SERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, json_field, array_array_field) \
  json[json_field] = nl::json::array();                                             \
  for (const auto& array: array_array_field) {                                      \
    nl::json arr = nl::json::array();                                               \
    for (const auto& e: array) {                                                    \
      arr.push_back(e->toJson());                                                   \
    }                                                                               \
    json[json_field].push_back(arr);                                                \
  }


/// Deserialize
#define OBJECT_DESERIALIZE_FIELD(json, json_field, field, default_value, optional)                \
  if (json.contains(json_field)) {                                                                \
    try {                                                                                         \
      using T = std::remove_reference_t<std::remove_const_t<decltype(field)>>;                    \
      field = json[json_field].get<T>();                                                          \
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
  }

#define OBJECT_DESERIALIZE_FIELD_PTR(json, json_field, field, optional)                           \
  if (json.contains(json_field)) {                                                                \
    using T = std::remove_reference_t<std::remove_const_t<decltype(field)>>;                      \
    using E = T::element_type;                                                                    \
    field.reset(new (E)(json[json_field]));                                                       \
  } else {                                                                                        \
    if (not(optional)) {                                                                          \
      std::ostringstream err{};                                                                   \
      err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \"" \
          << json_field << "\" from json object: " << json.dump(2);                               \
      throw Exception(err.str());                                                                 \
    }                                                                                             \
    field = nullptr;                                                                              \
  }

#define OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, json_field, array_field, optional)               \
  if ((json.contains(json_field)) and (json[json_field].is_array())) {                            \
    using T = std::remove_reference_t<std::remove_const_t<decltype(array_field)::value_type>>;    \
    using E = T::element_type;                                                                    \
    array_field.reserve(json[json_field].size());                                                 \
    for (const nl::json& obj: json[json_field]) {                                                 \
      array_field.emplace_back(new E(obj));                                                       \
    }                                                                                             \
  } else {                                                                                        \
    if (not(optional)) {                                                                          \
      std::ostringstream err{};                                                                   \
      err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \"" \
          << json_field << "\" from json object: " << json.dump(2);                               \
      throw Exception(err.str());                                                                 \
    }                                                                                             \
    array_field.clear();                                                                          \
  }


#define OBJECT_DESERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, json_field, array_array_field, optional)   \
  if ((json.contains(json_field)) and (json[json_field].is_array())) {                            \
    using ArrayArray = decltype(array_array_field);                                               \
    using Array = ArrayArray::value_type;         /* e.g vector<vector<int> <- > */               \
    using T = ArrayArray::value_type::value_type; /* e.g vector<vector<int>> <-  */               \
    using E = T::element_type;                                                                    \
    array_array_field.reserve(json[json_field].size());                                           \
    for (const nl::json& array: json[json_field]) {                                               \
      Array arr;                                                                                  \
      arr.reserve(array.size());                                                                  \
      for (const nl::json& obj: array) {                                                          \
        arr.emplace_back(new E(obj));                                                             \
      }                                                                                           \
      array_array_field.push_back(std::move(arr));                                                \
    }                                                                                             \
  } else {                                                                                        \
    if (not(optional)) {                                                                          \
      std::ostringstream err{};                                                                   \
      err << __FILE__ << ':' << __LINE__ << ": " << __FUNCTION__ << ": Missing required field \"" \
          << json_field << "\" from json object: " << json.dump(2);                               \
      throw Exception(err.str());                                                                 \
    }                                                                                             \
    array_array_field.clear();                                                                    \
  }
