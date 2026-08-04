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
        core/Renderer.cpp
        core/Renderer.h
        utils/RNG.h
        utils/Vec2.h
        Entities/Player.cpp
        Entities/Player.h
        Entities/Entity.cpp
        Entities/Entity.h
        Entities/Enemy.cpp
        Entities/Enemy.h
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
