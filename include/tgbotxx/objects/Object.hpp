#pragma once
#include <nlohmann/json.hpp>
#include <tgbotxx/utils/Ptr.hpp>
#include <type_traits>
#include <iostream>

namespace nl = nlohmann;

namespace tgbotxx {
    /// @brief Interface of all Objects.
    /// All objects must be serializable.
    struct Object {
        /// @brief Serialize object to JSON
        virtual nl::json toJson() const = 0;

        /// @brief Deserialize object from JSON
        virtual void fromJson(const nl::json &) = 0;
    };


/// @brief Helper macros to de/serialize objects

#define OBJECT_SERIALIZE_FIELD(json, json_field, field)  \
      json[json_field] = field;


#define OBJECT_SERIALIZE_FIELD_OPT(json, json_field, field, default_value)  \
  json[json_field] = field ? *field : default_value


#define OBJECT_DESERIALIZE_FIELD(json, json_field, field, default_value)                 \
  if (json.contains(json_field)) {                                               \
    using T = std::remove_reference_t<std::remove_const_t<decltype(field)>>; \
    field = json[json_field].get<T>();                                           \
  } else { field = default_value; std::cerr << "Could not deserialize field \""<<json_field<<"\" from json object: " << json.dump(2) << std::endl;  }


#define OBJECT_DESERIALIZE_FIELD_OPT(json, json_field, field)                            \
  if (json.contains(json_field)) {                                               \
    using T = std::remove_reference_t<std::remove_const_t<decltype(field)>>; \
    using E = T::element_type;                                               \
    field.reset(new (E)( json[json_field].get<E>() ));                           \
  } else { field.reset(); std::cerr << "Could not deserialize field \""<<json_field<<"\" from json object: " << json.dump(2) << std::endl;  }
}
