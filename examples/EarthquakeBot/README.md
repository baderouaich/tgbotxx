## earthquake_bot
This example shows how to program a Telegram Bot that will alert you if there is a recent earthquake somewhere in the world.

### Run
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8
./earthquake_bot YOUR_BOT_TOKEN
```

### How to create a new Bot and obtain its private token ?
1. Open the Telegram mobile app and search BotFather
2. Send BotFather a command /newbot
3. Follow instructions to create a new Bot
4. After you finish the instructions, you will receive a Bot Token, make sure you keep it secured.

### Commands
<img src="img/commands.jpg" alt="Commands" width="300"/>

### Alerts
<img src="img/alerts.jpg" alt="Alerts" width="300"/>

### Location
<img src="img/location.jpg" alt="Location" width="300"/>
