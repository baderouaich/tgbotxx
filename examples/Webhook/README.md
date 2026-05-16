## Webhook
This example shows how to program a Telegram Bot that uses a webhook instead of long polling.

### Run
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8

# Set env vars
export BOT_TOKEN=YOUR_BOT_TOKEN
export WEBHOOK_URL=https://bot.example.com/webhook
export WEBHOOK_PORT=36902
export WEBHOOK_CERT_FILE=/path/to/certs/selfsigned/certificate.crt
export WEBHOOK_PRIVATE_FILE=/path/to/certs/selfsigned/private.key

# Run the bot
./webhook_bot
```

### How to create a new Bot and obtain its private token ?
1. Open the Telegram mobile app and search BotFather
2. Send BotFather a command /newbot
3. Follow instructions to create a new Bot
4. After you finish the instructions, you will receive a Bot Token, make sure you keep it secured.