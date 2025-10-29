# ISEC - Object-Oriented Programming (POO) - Desert Travel Simulator (2024/2025)

## Context

This repository contains the project materials developed for the practical assignment of the **Object-Oriented Programming (POO)** course unit, part of the Computer Engineering degree at the Coimbra Institute of Engineering (ISEC), during the 2024/2025 academic year.

## Project Goal

The primary objective was to develop a **turn-based desert travel simulator** in **C++**, applying core Object-Oriented Programming principles. The simulator allows users to manage caravans, explore a desert map, interact with cities and items, and engage in combat with barbarian caravans.

## Key Aspects Covered

* **Object-Oriented Design:** Implementation based on **inheritance** (e.g., `Entidade` as a base for `Caravana`, `Cidade`, `Item`), **polymorphism** (handling different caravan types like `Comercio`, `Militar`, `PaiNatal`, `Barbara` uniformly), and **encapsulation**.
* **Core Game Entities:**
    * **Caravans:** Different types with unique attributes (load capacity, water, crew) and behaviors (movement, combat, trading, autonomous actions). Includes special types like `PaiNatal` (Santa Claus) and NPC `Barbara` caravans.
    * **Cities:** Locations for trade (buy/sell goods, hire crew, buy caravans), rest, and water replenishment.
    * **Items:** Randomly spawning items with diverse effects (`CaixaDePandora`, `ArcaDoTesouro`, `Jaula`, `Mina`, `Surpresa`).
    * **Map:** Grid-based environment with desert, mountains (impassable), and cities, read from a configuration file.
* **Game Mechanics:**
    * **Turn-based Simulation:** User inputs commands, then the simulation progresses (autonomous movements, resource consumption, combat, item spawning/decay).
    * **Command Line Interface:** Interaction via text commands parsed by the simulator.
    * **Console Buffer:** Custom `Buffer` class for managing screen output without direct cursor manipulation.
    * **Combat:** Automated combat between player caravans and barbarian caravans based on crew size.
    * **Resource Management:** Caravans consume water based on crew and time; lack of water impacts crew.
    * **Trade:** Buying and selling goods in cities.
    * **Sandstorms:** Event triggered by the user affecting caravans in a specified area.
* **C++ Features:**
    * **Standard Template Library (STL):** Use of `std::vector`, `std::map`, `std::set` for managing collections of entities.
    * **Smart Pointers (`std::shared_ptr`):** For automatic memory management of dynamically allocated objects (Entities).
    * **Exception Handling:** Custom exception classes (`SimuladorExcecao`, `ConfiguracaoExcecao`) for error management.

## Tools and Languages Used

* **Language:** C++
* **IDE:** CLion (inferred from file types and `.idea` folder)

## Repository Contents

| File / Folder              | Description                                                                                                                                  |
| :------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------- |
| **`/Sources/`** | **Contains the project setup folders** (`.idea`) and the main source code folder (`/tp/`).                                                    |
| **`/Sources/tp/`** | **Contains all C++ source code** (`.cpp`, `.h` files, `CMakeLists.txt`, `config.txt`, etc.).                                                            |
| `Relatório.pdf`            | The final project report detailing the implementation, class structure, and design choices.                                                 |
| `POO - 2425 - Enunciado Trabalho Pratico.pdf` | The original assignment brief (Enunciado) for the course unit.                                                                |

## Authors

* Diogo Silva
* André Tavares
