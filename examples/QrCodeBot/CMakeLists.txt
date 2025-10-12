cmake_minimum_required(VERSION 3.10)
project(qrcode_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(tgbotxx
        GIT_REPOSITORY "https://github.com/baderouaich/tgbotxx"
        GIT_TAG         "v1.1.9.2"
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(tgbotxx)

# Qr Code Processing Library
FetchContent_Declare(ZXing
        GIT_REPOSITORY "https://github.com/zxing-cpp/zxing-cpp"
        GIT_TAG master
        )
FetchContent_MakeAvailable(ZXing)

# Stb libs for image read/write
FetchContent_Declare(stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
)
FetchContent_MakeAvailable(stb)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC tgbotxx ZXing)
target_include_directories(${PROJECT_NAME} PUBLIC ${stb_SOURCE_DIR})