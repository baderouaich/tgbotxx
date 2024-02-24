### Local Telegram Api Server
If your Bot needs to exceed the default Telegram Api limits (file uploads size limits..etc), You should 
think of running your own Telegram Api server locally.

### Features
- Download files without a size limit. 
- Upload files up to 2000 MB.
- Upload files using their local path and the file URI scheme.
- Use an HTTP URL for the webhook.
- Use any local IP address for the webhook.
- Use any port for the webhook.
- Set max_webhook_connections up to 100000.
- Receive the absolute local path as a value of the file_path field without the need to download the file after a getFile request.

### Building and Starting a Telegram Bot API Local Server (Instructions)

To run a Telegram bot using the Telegram Bot API, follow these instructions.
These steps detail how to install and run the server locally.

#### Steps:

1. **Clone the Tdlib Repository:**
   ```bash
   $ git clone --recursive https://github.com/tdlib/telegram-bot-api.git
   $ cd telegram-bot-api
   ```
2. **Install required libraries**
Refer to build setup from this website https://tdlib.github.io/telegram-bot-api/build.html

3. **Build & Install Tdlib:**
   ```bash
   $ mkdir build && cd build
   $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:PATH=$HOME ..
   $ cmake -DCMAKE_BUILD_TYPE=Release ..
   $ cmake --build . --target install
    ```

4. **Obtain an app_id and app_hash**
Follow instructions in https://core.telegram.org/api/obtaining_api_id

6. **Start the Server:**
   ```bash
   $ telegram-bot-api --api-id $YOUR_TELEGRAM_API_ID --api-hash $YOUR_TELEGRAM_API_HASH --local &
   ```

7. **Access the Server:**
   You can access the local server using the IP `http://0.0.0.0:8081`. The default listening port for the Telegram API bot server is 8081 which you can set using `--http-port`
   You can treat `http://0.0.0.0:8081` the same way you will treat the default Telegram Api url `https://api.telegram.org` 

8. **Terminating the Server:**
   To terminate the server, find the process ID (PID) of the running `telegram-bot-api` server and use the `kill` command:
   ```bash
   $ ps aux | grep telegram-bot-api
   $ kill <PID>
   ```
   *OR*
    ```bash
   $ pkill telegram-bot-api
   ```
   
9. **Adjust Code for tgbotxx to use local server:**
   If you're using `tgbotxx`, adjust the API URL to point to your local server, before making any call to the api in the `Bot::onStart()` method:
   ```C++
   void MyBot::onStart() {
    api()->setUrl("http://0.0.0.0:8081"); 
    // .. rest of your code
   }
   ```


These steps should help you run a Telegram Api server locally with tgbotxx.
Adjustments may be needed based on your specific requirements and environment.
