#pragma once
#include <vector>
#include <tgbotxx/utils/Ptr.hpp>

namespace tgbotxx {
    class Api;
    struct Message;
    struct Update;

    class Bot {
        Ptr<Api> m_api;
        std::int32_t m_lastUpdateId;
        std::vector<Ptr<Update>> m_updates;
        bool m_running;

    public:
        explicit Bot(const std::string& token);

        void start();
        void stop();

    public: /// Bot Callbacks
        /// @brief Called when Bot is started (triggered by Bot::start())
        virtual void onStart() {}

        /// @brief Called when Bot is about to be stopped (triggered by Bot::stop())
        /// Cleanup your code in this callback (close handles, backup data...)
        virtual void onStop() {}

        /// @brief Called when a new message is received of any kind - text, photo, sticker, etc.
        /// @param message Received message object
        virtual void onAnyMessage(const Ptr<Message>& message) {}

        /// @brief Called when a non-command message is received of any kind - text, photo, sticker, etc.
        /// @param message Received non-command message object
        virtual void onNonCommandMessage(const Ptr<Message>& message) {}

        /// @brief Called when a new command is received (messages with leading '/' char).
        /// @param command Received command object
        virtual void onCommand(const Ptr<Message>& command) {}

        /// @brief Called when an unknown command is received (messages with leading '/' char).
        /// @param message Received unknown command object
        /// @note Known commands are set with Bot::setCommands()
        virtual void onUnknownCommand(const Ptr<Message>& message) {}

    protected: /// Setters

    protected: /// Getters
        const Ptr<Api>& getApi() const noexcept;

    private:
        /// @brief Dispatch update to callbacks
        /// @param update: Update to dispatch
        void dispatch(const Ptr<Update>& update);
    };

}