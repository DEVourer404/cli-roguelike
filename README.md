# ⚔️ CLI Roguelike Dungeon

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-3.29%2B-064F8C?logo=cmake)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

A lightweight, turn-based procedural dungeon crawler written in modern C++ (C++20) for the terminal. Features clean OOP architecture, smart pointers, zero memory leaks, and a custom cross-platform terminal input and rendering engine.

---

## Features

- **Procedural Generation & Room Types:**
  - Generates organic, connected caves using a random walk algorithm with directional momentum.
  - Dedicated **Shop Floors** featuring a friendly Merchant (`M`) and purchaseable items on the floor.
- **Turn-Based Combat & AI:**
  - Enemies track the player using a **Breadth-First Search (BFS)** pathfinding algorithm.
  - Core RPG stats system (Strength, Dexterity, Constitution) affecting damage, dodge chance, and maximum health.
  - Gold rewards and XP leveling system upon defeating monsters.
- **Economy & Merchant System:**
  - **Bump-to-talk:** Interact with the Merchant (`M`) for dungeon advice and full-heal services.
  - **Bump-to-buy:** Step onto shop floor items to preview prices and purchase with collected Gold.
- **Polymorphic Item & Equipment System:**
  - Weapons, Armor, and Consumables utilizing dynamic polymorphism and the Prototype Pattern (`clone()`).
  - Fixed-size inventory management (equip, use, drop).
- **Cross-Platform Terminal Engine:**
  - Custom I/O abstraction (`Terminal::getKey()`) using POSIX `termios` raw mode for Linux/macOS and console API for Windows.
  - ANSI escape codes for clean terminal rendering without platform-locked libraries.
- **Data-Driven Architecture:**
  - Enemy templates and item definitions loaded from JSON files via `nlohmann/json` (fetched automatically via CMake `FetchContent`).

## Screenshots

<p align="center">
  <img width="632" alt="main_menu" src="https://github.com/user-attachments/assets/fd0d4f30-abda-4ab5-9920-5b0593b398a6" />
  <br>
  <em>Main Menu & Navigation</em>
</p>
<p align="center">
   <img width="608" height="662" alt="controls_help" src="https://github.com/user-attachments/assets/035ed547-e43d-4040-90a8-83328fcffde1" />
  <br>
  <em>Controls & Help</em>
</p>
<p align="center">
  <img width="480" alt="fight_1" src="https://github.com/user-attachments/assets/13555c69-f1f8-4b71-a821-99afbc9587c4" />
  <br>
  <em>Dungeon Exploration & Turn-Based Combat</em>
</p>

---

## Controls

| Action | Primary Key | Secondary Key |
| :--- | :---: | :---: |
| **Movement (Up / Down / Left / Right)** | `W` / `S` / `A` / `D` | `↑` / `↓` / `←` / `→` |
| **Open Inventory** | `I` | - |
| **Wait / Skip Turn** | `SPACE` | - |
| **Back / Close Menu** | `Q` | `ESC` |
| **Select / Confirm** | `1` - `9` | `ENTER` |

---

## Project Structure

```text
├── core/         # Game loop, level orchestration, turn management (TurnManager), and UI rendering
├── entities/     # Entity hierarchy (Player, Enemy, base Entity)
├── items/        # Polymorphic item system (Weapon, Armor, Consumable, base Item)
├── systems/      # Procedural dungeon generation algorithms (LevelGenerator)
├── data/         # JSON data loader (nlohmann/json)
├── utils/        # Vector math (Vec2), RNG utilities, and cross-platform Terminal input
└── resources/    # enemies.json, items.json game configurations
```

---

## Building & Running

### Requirements
- C++20 compliant compiler (GCC 11+, Clang 13+, MSVC 2019+)
- CMake 3.20+

### Build Steps

```bash
# 1. Clone repository
git clone https://github.com/DEVourer404/CLI-Roguelike.git
cd CLI-Roguelike

# 2. Configure project
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 3. Build
cmake --build build --config Release
```

### Run

- **Windows:**
  ```powershell
  .\build\Release\CLI_Roguelike.exe
  ```
- **Linux / macOS:**
  ```bash
  ./build/CLI_Roguelike
  ```

---

## Code Quality & CI

- **Compiler Warnings:** Configured with strict warnings (`-Wall -Wextra -Wpedantic` on GCC/Clang, `/W4` on MSVC) ensuring a 0-warning build.
- **Continuous Integration:** Multi-platform automated builds on **Ubuntu**, **Windows**, and **macOS** via GitHub Actions.

---

## Roadmap / Planned Features

- [ ] **Unit Tests:** Integration of a unit testing framework (Catch2 / GoogleTest) for combat math, procedural generation, and pathfinding.
- [ ] **Continuous Delivery (CD):** Automated packaging and multi-platform release generation on GitHub Actions for tagged versions.
- [ ] **Dedicated Terminal / TUI Engine:** Potential migration to a dedicated terminal UI / gamedev library (e.g., FTXUI, PDCurses, or libtcod) for enhanced rendering and advanced color palette support.
- [ ] **Combat Expansion:** Active skills, status effects (poison, stun), and ranged combat.
- [ ] **Advanced AI & Fog of War:** Field of View (FOV / shadowcasting) and distinct enemy archetypes (ranged, fleeing, aggressive).
- [ ] **Content Expansion:** Wider selection of enemy types, weapons, armors, and consumables.
- [x] **Special Floor Types:** Shopkeeper / merchant levels with item purchasing and healing services.
- [ ] **Boss Encounters & Shrines:** Boss fights on specific milestone floors and shrine buff interactions.
