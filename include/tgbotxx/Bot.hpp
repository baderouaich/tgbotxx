#pragma once
#include <atomic>
#include <tgbotxx/utils/Ptr.hpp>

namespace tgbotxx {
    class Api;
    class Message;
    class BotCommand;
    class Update;

    class Bot {
        std::string m_token;
        Ptr<Api> m_api;
        //Ptr<std::thread> m_thread;
        std::atomic<bool> m_running;
        std::int32_t m_lastUpdateId;

    public:
        explicit Bot(const std::string& token);

        void start();
        void stop();
        void restart();

    public: /// Bot Callbacks
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