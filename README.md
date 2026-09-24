# ⚔️ CLI Roguelike Dungeon

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-3.29%2B-064F8C?logo=cmake)](https://cmake.org/)
[![C++ CI](https://github.com/DEVourer404/CLI-Roguelike/actions/workflows/ci.yml/badge.svg)](https://github.com/DEVourer404/CLI-Roguelike/actions)
[![GoogleTest](https://img.shields.io/badge/GoogleTest-v1.15.2-brightgreen.svg)](https://github.com/google/googletest)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()
[![Status](https://img.shields.io/badge/Status-Alpha%20v0.1.0-orange.svg)]()

A lightweight, turn-based procedural dungeon crawler written in modern C++ (C++20) for the terminal. Features clean object-oriented architecture, comprehensive GoogleTest unit test coverage, and a custom cross-platform terminal input and rendering engine.

---

## 🎮 Features

- **Procedural Generation & Special Floor Types:**
  - Organic, interconnected cave generation via random walk with directional momentum.
  - Dedicated **Shop Floors** with an interactive Merchant (`M`) and floor-based item purchasing.
- **Turn-Based Combat & Enemy AI:**
  - Enemies track the player using a **Breadth-First Search (BFS)** pathfinding algorithm.
  - RPG progression system: Strength, Dexterity, Constitution affecting damage, dodge chance, and max health.
  - Experience points, leveling up with stat allocation, and gold rewards on monster defeat.
- **In-Game Event Logger:**
  - Boxed FIFO message history displaying the 5 most recent actions (`[Log 1]` - `[Log 5]`).
  - Real-time logging of combat encounters, dodge rolls, inventory transactions, and dialogs.
- **Economy & Merchant System:**
  - **Bump-to-talk:** Interact with the Merchant (`M`) for dungeon advice and healing.
  - **Bump-to-buy:** Step onto items in shops to preview prices and purchase with collected Gold.
- **Polymorphic Item & Equipment System:**
  - Weapons, Armor, and Consumables utilizing runtime polymorphism and the Prototype Pattern (`clone()`).
  - 8-slot inventory with item usage, automatic slot shifting, and equipment toggling.
- **Cross-Platform Terminal Engine:**
  - Zero third-party GUI dependencies. Custom I/O abstraction (`Terminal::getKey()`) using POSIX `termios` raw mode on Unix and Windows Console API on Windows.
  - ANSI escape sequences for flicker-free terminal clearing and rendering.
- **Data-Driven Architecture:**
  - Monster stats and item templates loaded dynamically from JSON files via `nlohmann/json`.

---

## 📸 Screenshots

<p align="center">
  <img width="632" alt="main_menu" src="https://github.com/user-attachments/assets/fd0d4f30-abda-4ab5-9920-5b0593b398a6" />
  <br><em>Main Menu & Navigation</em>
</p>
<p align="center">
  <img width="505" height="561" alt="controls help" src="https://github.com/user-attachments/assets/948d5784-3be5-488f-817c-50a0e06c6673" />
  <br><em>Controls & Help</em>
</p>
<p align="center">
  <img width="480" alt="fight_1" src="https://github.com/user-attachments/assets/13555c69-f1f8-4b71-a821-99afbc9587c4" />
  <br><em>Dungeon Exploration & Turn-Based Combat</em>
</p>
<p align="center">
  <img width="487" height="468" alt="merchant" src="https://github.com/user-attachments/assets/8b889a96-6b74-42b1-b60b-d8d9635354fe" />
  <br><em>Dungeon Merchant level</em>
</p>

---

## 🕹️ Controls

| Action | Primary Key | Secondary Key |
| :--- | :---: | :---: |
| **Movement (Up / Down / Left / Right)** | `W` / `S` / `A` / `D` | `↑` / `↓` / `←` / `→` |
| **Open Inventory** | `I` | - |
| **Wait / Skip Turn** | `SPACE` | - |
| **Back / Close Menu** | `Q` | `ESC` |
| **Select / Confirm** | `1` - `9` | `ENTER` |

---

## 🏗️ Architecture & Engineering Highlights

- **Modern C++20 Idioms:** Standard attributes, `std::format`, `std::unique_ptr` ownership transfer, and strong type safety.
- **Prototype Pattern:** Deep-cloning item generation using virtual `clone()` methods.
- **Graph Search Algorithms:** BFS-based pathfinding for tactical enemy movement and obstacle avoidance.
- **Clean Layered Architecture:** Decoupled simulation loop (`TurnManager`), rendering (`Renderer`), and map state (`Level`).
- **Comprehensive Unit Testing:** 6 GoogleTest test suites following the strict **AAA (Arrange-Act-Assert)** pattern.

---

## 📂 Project Structure

```text
├── core/         # Turn loop, Level state, Logger, and Renderer
├── entities/     # Entity hierarchy (Player, Enemy, base Entity)
├── items/        # Polymorphic item system (Weapon, Armor, Consumable, base Item)
├── systems/      # Procedural dungeon generation (LevelGenerator)
├── data/         # JSON data loaders (JsonLoader)
├── utils/        # Vector math (Vec2), RNG utilities, and cross-platform Terminal input
├── resources/    # enemies.json, items.json game configurations
└── tests/        # GoogleTest suite (player, items, enemy BFS, combat, level, utils)
```

---

## ⚙️ Building, Running & Testing

### Requirements
- C++20 compliant compiler (GCC 11+, Clang 13+, MSVC 2019+)
- CMake 3.20+

### Build

```bash
# 1. Clone repository
git clone https://github.com/DEVourer404/CLI-Roguelike.git
cd CLI-Roguelike

# 2. Configure project
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 3. Compile game & tests
cmake --build build --config Release
```

### Run Game

- **Windows:**
  ```powershell
  .\build\Release\CLI_Roguelike.exe
  ```
- **Linux / macOS:**
  ```bash
  ./build/CLI_Roguelike
  ```

### Run Unit Tests

All unit tests are registered via CTest and execute across all platforms in CI:

```bash
ctest --test-dir build -C Release --output-on-failure
```

Or execute the test runner binary directly:
- **Windows:** `.\build\Release\CLI_Roguelike_Tests.exe`
- **Linux / macOS:** `./build/CLI_Roguelike_Tests`

---

## 🛡️ Code Quality & CI

- **Strict Warnings:** Compiled with `-Wall -Wextra -Wpedantic` (GCC/Clang) and `/W4` (MSVC) for zero-warning builds.
- **Continuous Integration:** Multi-platform build and automated test runs on **Ubuntu**, **Windows**, and **macOS** via GitHub Actions.
- **Memory Safety:** Deterministic resource management using RAII and smart pointers (`std::unique_ptr`).
