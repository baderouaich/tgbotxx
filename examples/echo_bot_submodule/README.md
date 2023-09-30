## echo_bot_submodule
This example shows how to use tgbotxx as a submodule to program a Telegram Bot that echoes your messages back.

## Steps
1. git clone or git submodule add the library in your project libraries directory:
```shell
git submodule add https://github.com/baderouaich/tgbotxx ./lib/tgbotxx
```
or 
```shell
git clone https://github.com/baderouaich/tgbotxx ./lib/tgbotxx
``` 

2. Then add `add_subdirectory(lib/tgbotxx)` in your `CMakeLists.txt`.
```cmake
cmake_minimum_required(VERSION 3.10)
project(my_bot_project)

add_subdirectory(lib/tgbotxx) # <-- clone tgbotxx in your lib/ directory
include_directories(lib/tgbotxx/include) # <-- include tgbotxx/ headers

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC tgbotxx) # <-- link to tgbotxx
```

3. Build your Bot:
```shell
mkdir build && cd build
cmake .. 
make 
```