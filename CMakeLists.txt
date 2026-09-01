cmake_minimum_required(VERSION 3.29)
project(CLI_Roguelike)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# External dependencies
include(FetchContent)

# nlohmann_json
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(json)

# GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
)

# For Windows MSVC: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Core game library
add_library(CLI_Roguelike_Lib STATIC
        core/Game.cpp
        core/Map.cpp
        core/ConsoleUI.cpp
        core/Level.cpp
        core/TurnManager.cpp

        systems/LevelGenerator.cpp

        entities/Player.cpp
        entities/Entity.cpp
        entities/Enemy.cpp

        items/Item.cpp
        items/Weapon.cpp
        items/Armor.cpp
        items/Consumable.cpp

        data/JsonLoader.cpp
)

target_include_directories(CLI_Roguelike_Lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(WIN32)
    target_sources(CLI_Roguelike_Lib PRIVATE
            utils/Input_win.cpp
    )
else()
    target_sources(CLI_Roguelike_Lib PRIVATE
            utils/Input_posix.cpp
    )
endif()

target_link_libraries(CLI_Roguelike_Lib PUBLIC nlohmann_json::nlohmann_json)

# Main game executable
add_executable(CLI_Roguelike
        main.cpp
)

target_link_libraries(CLI_Roguelike PRIVATE CLI_Roguelike_Lib)

add_custom_command(TARGET CLI_Roguelike POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:CLI_Roguelike>/resources"
)

# Tests
enable_testing()

add_executable(CLI_Roguelike_Tests
        tests/test_player.cpp
        tests/test_items.cpp
        tests/test_enemy.cpp
        tests/test_utils.cpp
        tests/test_combat.cpp
        tests/test_level.cpp
)

target_link_libraries(CLI_Roguelike_Tests PRIVATE
        CLI_Roguelike_Lib
        GTest::gtest_main
)

add_custom_command(TARGET CLI_Roguelike_Tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:CLI_Roguelike_Tests>/resources"
)

include(GoogleTest)
gtest_discover_tests(CLI_Roguelike_Tests)

# Compiler warnings
if(MSVC)
    target_compile_options(CLI_Roguelike_Lib PRIVATE /W4)
    target_compile_options(CLI_Roguelike PRIVATE /W4)
    target_compile_options(CLI_Roguelike_Tests PRIVATE /W4)
else()
    target_compile_options(CLI_Roguelike_Lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(CLI_Roguelike PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(CLI_Roguelike_Tests PRIVATE -Wall -Wextra -Wpedantic)
endif()
