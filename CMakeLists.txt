cmake_minimum_required(VERSION 3.29)
project(CLI_Roguelike)

set(CMAKE_CXX_STANDARD 20)

# adding json library
include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(json)

add_executable(CLI_Roguelike
        main.cpp

        core/Game.cpp
        core/Map.cpp
        core/ConsoleUI.cpp
        core/Level.cpp
        core/Combat.cpp

        systems/DungeonGenerator.cpp

        entities/Player.cpp
        entities/Entity.cpp
        entities/Enemy.cpp

        items/Item.cpp
        items/Weapon.cpp
        items/Armor.cpp
        items/Consumable.cpp

        data/JsonLoader.cpp
)

target_include_directories(CLI_Roguelike PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(WIN32)
    target_sources(CLI_Roguelike PRIVATE
            utils/Input_win.cpp
    )
else()
    target_sources(CLI_Roguelike PRIVATE
            utils/Input_posix.cpp
    )
endif()

target_link_libraries(CLI_Roguelike PRIVATE nlohmann_json::nlohmann_json)
add_custom_command(TARGET CLI_Roguelike POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:CLI_Roguelike>/resources"
)

if(MSVC)
    target_compile_options(CLI_Roguelike PRIVATE /W4)
else()
    target_compile_options(CLI_Roguelike PRIVATE -Wall -Wextra -Wpedantic)
endif()