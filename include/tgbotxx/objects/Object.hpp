#pragma once
/// Available objects: https://core.telegram.org/bots/api#available-types
#include <tgbotxx/utils/Ptr.hpp>
#include <tgbotxx/Exception.hpp>
#include <cstdint>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
namespace nl = nlohmann;

/// @brief Helper macros to de/serialize objects

/// Serialize
#define OBJECT_SERIALIZE_FIELD(json, json_field, field) \
  json[json_field] = field;

#define OBJECT_SERIALIZE_FIELD_PTR(json, json_field, field, default_value) \
  json[json_field] = field ? field->toJson() : default_value

#define OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, json_field, array_field) \
  json[json_field] = nl::json::array();                                 \
  for(const auto& e : array_field)                                      \
    json[json_field].push_back(e->toJson());

/// Deserialize
#define OBJECT_DESERIALIZE_FIELD(json, json_field, field, default_value, optional)                                       \
  if (json.contains(json_field))                                                                                         \
  {                                                                                                                      \
    try {                                                                                                                \
      using T = std::remove_reference_t<std::remove_const_t<decltype(field)>>;                                           \
      field = json[json_field].get<T>();                                                                                 \
    } catch(const std::exception& e) {                                                                                   \
      std::ostringstream err{};                                                                                          \
      err << __FILE__ << ':' << __LINE__ <<": "<<__PRETTY_FUNCTION__<<": Failed to deserialize \""                       \
      << json_field << "\" from json object: " << json.dump(2) << "\nReason: " << e.what();                              \
      throw Exception(err.str());                                                                                        \
    } catch(...) {                                                                                                       \
      std::ostringstream err{};                                                                                          \
      err << __FILE__ << ':' << __LINE__ <<": "<<__PRETTY_FUNCTION__<<": Failed to deserialize \""                       \
      << json_field << "\" from json object: " << json.dump(2);                                                          \
      throw Exception(err.str());                                                                                        \
    }                                                                                                                    \
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

#define OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, json_field, array_field, optional)                                      \
  if ((json.contains(json_field)) and (json[json_field].is_array()))                                                     \
  {                                                                                                                      \
    using T = std::remove_reference_t<std::remove_const_t<decltype(array_field)::value_type>>;                           \
    using E = T::element_type;                                                                                           \
    array_field.reserve(json[json_field].size());                                                                        \
    for(const nl::json& obj : json[json_field]) {                                                                        \
        array_field.emplace_back(new E(obj));                                                                            \
    }                                                                                                                    \
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
    array_field.clear();                                                                                                 \
  }
