#pragma once
#include <thread>
#include <atomic>
#include "utils/Ptr.hpp"
#include "Api.hpp"

namespace tgbotxx {
    class Message;
    class Command;
    class Update;

    class Bot {
        std::string m_token;
        Ptr<Api> m_api;
        //Ptr<std::thread> m_thread;
        std::atomic<bool> m_running;

    public:
        Bot(const std::string& token);

        void start();
        void stop();
        void restart();

    public: /** Bot Callbacks */
        /**
         * @brief Called when a new message is received of any kind - text, photo, sticker, etc.
         * @param message Received message object
         */
        virtual void onAnyMessage(const Ptr<Message>& message) = 0;

        /**
         * @brief Called when a new command is received (messages with leading '/' char).
         * @param command Received command object
         */
        virtual void onCommand(const Ptr<Command>& command) = 0;

    protected:
        const Ptr<Api>& getApi() const noexcept;
    };

}