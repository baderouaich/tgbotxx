include(${CMAKE_CURRENT_LIST_DIR}/find-or-fetch.cmake)
# Find or download all dependencies
set(FIND_OR_FETCH_LIBS "")
## cURL cpr
# Find the cpr library, or download it in build/_deps
find_or_fetch(
        cpr
        https://github.com/libcpr/cpr.git
        31251f2b726fb954b0f2503ef3e1b72bfa773e50 # The commit hash for 1.10.4. Replace with the latest from: https://github.com/libcpr/cpr/releases
)
list(APPEND FIND_OR_FETCH_LIBS cpr::cpr)
# nlohmann json
# Find the nlohmann json library, or download it in build/_deps
find_or_fetch(
        nlohmann_json
        https://github.com/nlohmann/json
        GIT_TAG bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d # The commit hash for 3.11.2. Replace with the latest from: https://github.com/nlohmann/json/releases
)
list(APPEND FIND_OR_FETCH_LIBS nlohmann_json::nlohmann_json)
FetchContent_MakeAvailable(${remote_dependencies})