#pragma once
/// Available objects: https://core.telegram.org/bots/api#available-types
#include <cstdint>
#include <string>
#include <memory>
#include <tgbotxx/utils/Ptr.hpp>
#include <tgbotxx/Exception.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
namespace nl = nlohmann;

/// @brief Helper macros to de/serialize objects
#define OBJECT_SERIALIZE_FIELD(json, json_field, field) \
  json[json_field] = field;

#define OBJECT_SERIALIZE_FIELD_PTR(json, json_field, field, default_value) \
  json[json_field] = field ? field->toJson() : default_value

#define OBJECT_DESERIALIZE_FIELD(json, json_field, field, default_value, optional)                                       \
  if (json.contains(json_field))                                                                                         \
  {                                                                                                                      \
    using T = std::remove_reference_t<std::remove_const_t<decltype(field)>>;                                             \
    field = json[json_field].get<T>();                                                                                   \
  }                                                                                                                      \
  else                                                                                                                   \
  {                                                                                                                      \
    if(not (optional))                                                                                                   \
    {                                                                                                                    \
      std::ostringstream err{};                                                                                          \
      err << __FILE__ << ':' << __LINE__ <<": "<<__PRETTY_FUNCTION__<<": Missing required field \""                      \
      << json_field << "\" from json object: " << json.dump(2);                                                          \
      throw Exception(err.str());                                                                                        \
    }                                                                                                                    \
    field = default_value;                                                                                               \
  }

#define OBJECT_DESERIALIZE_FIELD_PTR(json, json_field, field, optional)                                                  \
  if (json.contains(json_field))                                                                                         \
  {                                                                                                                      \
    using T = std::remove_reference_t<std::remove_const_t<decltype(field)>>;                                             \
    using E = T::element_type;                                                                                           \
    field.reset(new (E)(json[json_field]));                                                                              \
  }                                                                                                                      \
  else                                                                                                                   \
  {                                                                                                                      \
    if(not (optional))                                                                                                   \
    {                                                                                                                    \
      std::ostringstream err{};                                                                                          \
      err << __FILE__ << ':' << __LINE__ <<": "<<__PRETTY_FUNCTION__<<": Missing required field \""                      \
      << json_field << "\" from json object: " << json.dump(2);                                                          \
      throw Exception(err.str());                                                                                        \
    }                                                                                                                    \
    field = nullptr;                                                                                                     \
  }