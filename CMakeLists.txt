cmake_minimum_required(VERSION 3.29)
project(CLI_Roguelike)

set(CMAKE_CXX_STANDARD 20)

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
