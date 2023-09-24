#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents a service message about a user allowing a bot to write messages after adding it to the attachment menu,
    /// launching a Web App from a link, or accepting an explicit request from a Web App sent by the method requestWriteAccess.
    /// @ref https://core.telegram.org/bots/api#writeaccessallowed
    struct WriteAccessAllowed {
        explicit WriteAccessAllowed(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Optional. True, if the access was granted after the user accepted an explicit request from a Web App sent by the method requestWriteAccess
        bool fromRequest;

        /// @brief Optional. Name of the Web App, if the access was granted when the Web App was launched from a link
        std::string webAppName;

        /// @brief Optional. True, if the access was granted when the bot was added to the attachment or side menu
        bool fromAttachmentMenu;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "from_request", fromRequest);
          OBJECT_SERIALIZE_FIELD(json, "web_app_name", webAppName);
          OBJECT_SERIALIZE_FIELD(json, "from_attachment_menu", fromAttachmentMenu);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "from_request", fromRequest, false, true);
          OBJECT_DESERIALIZE_FIELD(json, "web_app_name", webAppName, "", true);
          OBJECT_DESERIALIZE_FIELD(json, "from_attachment_menu", fromAttachmentMenu, false, true);
        }
    };
}