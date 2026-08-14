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

add_executable(CLI_Roguelike main.cpp
        core/Game.cpp
        core/Game.h
        systems/DungeonGenerator.cpp
        systems/DungeonGenerator.h
        core/Map.cpp
        core/Map.h
        core/ConsoleUI.cpp
        core/ConsoleUI.h
        utils/Rng.h
        utils/Vec2.h
        entities/Player.cpp
        entities/Player.h
        entities/Entity.cpp
        entities/Entity.h
        entities/Enemy.cpp
        entities/Enemy.h
        core/Level.cpp
        core/Level.h
        core/Combat.cpp
        core/Combat.h
        items/Item.cpp
        items/Item.h
        items/Weapon.cpp
        items/Weapon.h
        items/Armor.cpp
        items/Armor.h
        items/Consumable.cpp
        items/Consumable.h
        data/JsonLoader.cpp
        data/JsonLoader.h)

target_link_libraries(CLI_Roguelike PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(TARGET CLI_Roguelike POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:CLI_Roguelike>/resources"
)