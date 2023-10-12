## Weather Bot
This example shows how to program a Telegram Bot that displays the weather information of a city using the [weather api](https://www.weatherapi.com/). 

### Run
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8
./weather_bot YOUR_BOT_TOKEN WEATHER_API_KEY
```

### How to create a new Bot and obtain its private token ?
1. Open the Telegram mobile app and search BotFather
2. Send BotFather a command /newbot
3. Follow instructions to create a new Bot
4. After you finish the instructions, you will receive a Bot Token, make sure you keep it secured.

### Preview
<img src="img/preview.jpg" alt="Preview" width="300"/>
