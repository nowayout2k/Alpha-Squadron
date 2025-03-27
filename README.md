# No Way Out Game Engine

Welcome to the **No Way Out Game Engine**! This repository contains two main parts:

1. **Engine** – A modular, SFML-based 2D game engine, placed under the `Engine` namespace.
2. **Game** – A sample game (in the `AlphaSquadron` namespace) demonstrating how to use the engine to build a 2D game.

This README provides a comprehensive overview of the project structure, a detailed breakdown of each system with associated files, and information about how the engine and sample game are organized.

---

## Table of Contents

- [Project Structure Overview](#project-structure-overview)
- [Engine Namespace (Core Engine)](#engine-namespace-core-engine)
  - [Core & State Management](#core--state-management)
  - [GUI System](#gui-system)
  - [Rendering & Scene Graph](#rendering--scene-graph)
  - [Effects & Animation](#effects--animation)
  - [Audio System](#audio-system)
  - [Input & Key Binding](#input--key-binding)
  - [Resource Management](#resource-management)
  - [Parallel Tasks & Misc](#parallel-tasks--misc)
- [Game Namespace (Sample Game)](#game-namespace-sample-game)
  - [World & Entities](#world--entities)
  - [UI & States](#ui--states)
  - [Multiplayer](#multiplayer)
  - [Game Data & Configuration](#game-data--configuration)
- [Additional Notes on Systems](#additional-notes-on-systems)

---


Below is a detailed breakdown of the new directory structure, the purpose of each folder, and how the engine and game layers interact.



## Project Structure

```plaintext
.
├── Headers
│   ├── Engine
│   │   ├── Animation.h
│   │   ├── Audio.h
│   │   ├── AudioNode.h
│   │   ├── BloomEffect.h
│   │   ├── Button.h
│   │   ├── Cache.h
│   │   ├── Command.h
│   │   ├── CommandQueue.h
│   │   ├── Component.h
│   │   ├── Container.h
│   │   ├── Debug.h
│   │   ├── EmitterNode.h
│   │   ├── EmptyWorldNode.h
│   │   ├── Engine.h
│   │   ├── FontId.h
│   │   ├── GameSprite.h
│   │   ├── GameText.h
│   │   ├── KeyBinding.h
│   │   ├── Layer.h
│   │   ├── LoadingState.h
│   │   ├── NetworkNode.h
│   │   ├── ParallelTask.h
│   │   ├── Particle.h
│   │   ├── ParticleSystemNode.h
│   │   ├── PostEffect.h
│   │   ├── ShaderId.h
│   │   ├── SoundFxId.h
│   │   ├── State.h
│   │   ├── StateStack.h
│   │   ├── Utility.h
│   │   └── WorldNode.h
│   └── Game
│       ├── Aircraft.h
│       ├── AiRoutine.h
│       ├── CanvasNode.h
│       ├── DataTables.h
│       ├── Direction.h
│       ├── GameOverState.h
│       ├── MenuState.h
│       ├── MultiplayerGameState.h
│       ├── MusicId.h
│       ├── NodeType.h
│       ├── ParticleType.h
│       ├── PauseState.h
│       ├── Pickup.h
│       ├── PickupType.h
│       ├── Projectile.h
│       ├── ProjectileType.h
│       ├── ResourceManager.h
│       ├── SettingsState.h
│       ├── StateIdentifiers.h
│       ├── TitleState.h
│       └── World.h
├── Source
│   ├── Engine
│   │   ├── Animation.cpp
│   │   ├── Audio.cpp
│   │   ├── BloomEffect.cpp
│   │   ├── Button.cpp
│   │   ├── Component.cpp
│   │   ├── Container.cpp
│   │   ├── Debug.cpp
│   │   ├── EmitterNode.cpp
│   │   ├── EmptyWorldNode.cpp
│   │   ├── Engine.cpp
│   │   ├── GameSprite.cpp
│   │   ├── KeyBinding.cpp
│   │   ├── Label.cpp
│   │   ├── LoadingState.cpp
│   │   ├── NetworkNode.cpp
│   │   ├── ParallelTask.cpp
│   │   ├── ParticleSystemNode.cpp
│   │   ├── PostEffect.cpp
│   │   ├── State.cpp
│   │   ├── StateStack.cpp
│   │   ├── Utility.cpp
│   │   └── WorldNode.cpp
│   └── Game
│       ├── Aircraft.cpp
│       ├── CanvasNode.cpp
│       ├── DataTables.cpp
│       ├── Direction.cpp
│       ├── GameOverState.cpp
│       ├── GameServer.cpp
│       ├── MenuState.cpp
│       ├── MultiplayerGameState.cpp
│       ├── MusicId.cpp
│       ├── NodeType.cpp
│       ├── ParticleType.cpp
│       ├── PauseState.cpp
│       ├── Pickup.cpp
│       ├── PickupType.cpp
│       ├── Projectile.cpp
│       ├── ProjectileType.cpp
│       ├── ResourceManager.cpp
│       ├── SettingsState.cpp
│       ├── SoundFxId.cpp
│       ├── StateIdentifiers.cpp
│       ├── TitleState.cpp
│       └── World.cpp
├── Assets
│   ├── Textures
│   ├── SFX
│   ├── Fonts
│   └── Shaders
├── DataFiles
│   └── (JSON configuration files)
└── main.cpp
```
## Engine Namespace (Core Engine)

All engine-related code is under `Headers/Engine` and `Source/Engine`. The engine is divided into several **systems**. Each system is explained below, along with the associated files.

### 1. Core & State Management

- **Core Loop & State Control**  
  - **`Engine.h` / `Engine.cpp`**  
    Main engine class providing the primary game loop, window management, and the state stack setup.
  - **`State.h` / `State.cpp`**  
    Abstract base class for all game states. Each state implements `render()`, `update()`, and `handleEvent()`.
  - **`StateStack.h` / `StateStack.cpp`**  
    Manages a stack of states, with deferred push/pop/clear operations.
  - **`Command.h` / `CommandQueue.h`**  
    Encapsulates actions sent to scene-graph nodes. `DerivedAction` helps apply commands to specific node types.
  - **`Utility.h` / `Utility.cpp`**  
    Helper functions (math, random, string conversions, key to string) used throughout the engine.
  - **`Debug.h` / `Debug.cpp`**  
    Logging, toggles for FPS display, and collider visualization. Useful for diagnosing runtime issues.

### 2. GUI System

- **GUI Components**  
  - **`Component.h` / `Component.cpp`**  
    Abstract base for all GUI elements (buttons, labels, containers).
  - **`Container.h` / `Container.cpp`**  
    Composite component that holds child GUI elements and handles navigation.
  - **`Button.h` / `Button.cpp`**  
    A clickable GUI button with a callback. Supports selection, toggling, and activation.
  - **`Label.h` / `Label.cpp`**  
    A non-interactive text component for displaying labels or static text.

- **Loading Screen**  
  - **`LoadingState.h` / `LoadingState.cpp`**  
    A state showing a loading screen with a progress bar, while a `ParallelTask` loads resources in a separate thread.

### 3. Rendering & Scene Graph

- **Node Hierarchy**  
  - **`WorldNode.h` / `WorldNode.cpp`**  
    Base class for the scene graph, supporting hierarchical transformations, collision checks, and rendering.
  - **`EmptyWorldNode.h` / `EmptyWorldNode.cpp`**  
    Minimal node implementation used for placeholder or non-visual layers.
  - **`NetworkNode.h` / `NetworkNode.cpp`**  
    Collects and polls network-related actions (multiplayer events) within the scene graph.

- **Sprites & Text**  
  - **`GameSprite.h` / `GameSprite.cpp`**  
    A drawable node with texture loading, velocity-based movement, and collision bounding.
  - **`GameText.h`**  
    A node for displaying text in the world. (Implementation may be in the same file or separate `GameText.cpp`.)

- **Particle Systems**  
  - **`EmitterNode.h` / `EmitterNode.cpp`**  
    Continuously emits particles into a particle system.
  - **`ParticleSystemNode.h` / `ParticleSystemNode.cpp`**  
    Manages, updates, and renders a collection of particles.
  - **`Particle.h`**  
    Defines a single particle’s properties (position, color, lifetime).

### 4. Effects & Animation

- **Animation**  
  - **`Animation.h` / `Animation.cpp`**  
    Manages frame-based animations, including loop settings, duration, and frame size.

- **Post-Processing**  
  - **`PostEffect.h` / `PostEffect.cpp`**  
    Abstract class for post-processing effects (e.g., bloom).
  - **`BloomEffect.h` / `BloomEffect.cpp`**  
    Implements bloom via multiple render passes (brightness filtering, down sampling, and Gaussian blur).

### 5. Audio

- **`Audio.h` / `Audio.cpp`**  
  Manages sound effects and music, including positional audio using `sf::Listener`.
- **`AudioNode.h`**  
  Integrates audio playback into the scene graph. Plays sounds and music at node positions.

### 6. Input & Key Binding

- **`KeyBinding.h` / `KeyBinding.cpp`**  
  Maps keyboard keys to actions. Detects realtime actions and updates states accordingly.

### 7. Parallel Tasks & Misc

- **`ParallelTask.h` / `ParallelTask.cpp`**  
  Allows background loading or processing in a separate thread without blocking the main loop.
- **`Layer.h`**  
  Enumerates layers (Background, UI, etc.) used in rendering order.
- **`ShaderId.h`**, **`SoundFxId.h`**, **`FontId.h`**  
  Enumerations for shaders, sound effects, and fonts used by the engine.
- **`Cache.h`**  
  A generic caching class used by resource managers to load and store assets.

---

## Game Namespace (Sample Game)

All sample-game-related code is under `Headers/Game` and `Source/Game`. It uses the **Engine** namespace to demonstrate how to build a 2D game.

### 1. World & Entities

- **`World.h` / `World.cpp`**  
  Demonstrates a custom `World` class integrating the scene graph, scrolling, collision handling, and gameplay logic.
- **`Aircraft.h` / `Aircraft.cpp`**  
  Example entity derived from `GameSprite`, with specialized behavior like firing, health, AI movement.
- **`Pickup.h` / `Pickup.cpp`**  
  Represents collectible items (health, power-ups) that players can pick up.
- **`Projectile.h` / `Projectile.cpp`**  
  Bullet or missile logic, including guided missiles and damage handling.

### 2. UI & States

- **`CanvasNode.h` / `CanvasNode.cpp`**  
  Renders UI elements (e.g., health bars) within the scene graph.
- **`MenuState.h` / `MenuState.cpp`**  
  Shows a main menu with buttons to start the game, access settings, etc.
- **`PauseState.h` / `PauseState.cpp`**  
  Displays a pause menu overlay.
- **`SettingsState.h` / `SettingsState.cpp`**  
  Lets players rebind keys, showing a UI with current key assignments.
- **`GameOverState.h` / `GameOverState.cpp`**  
  Handles the end-of-game scenario, displaying a message before returning to the menu.
- **`TitleState.h` / `TitleState.cpp`**  
  Shows a title screen with logo and prompt to continue.

### 3. Multiplayer

- **`MultiplayerGameState.h` / `MultiplayerGameState.cpp`**  
  Demonstrates a state for networked multiplayer. Manages server connections, syncing the world, and player input.
- **`GameServer.h` / `GameServer.cpp`**  
  Handles server-side logic for hosting a multiplayer session (connections, packet processing, timeouts, etc.).
- **`NetworkProtocol.h`**  
  Defines packet types and structures for server-client communication (spawn events, movement updates, etc.).

### 4. Data & Configuration

- **`DataTables.h` / `DataTables.cpp`**  
  Structures storing entity configurations (health, speed, AI routines) loaded from JSON.
- **`Direction.h`, `ParticleType.h`, `PickupType.h`, `ProjectileType.h`, `MusicId.h`, `NodeType.h`**  
  Enumerations for directions, particle types, pickups, projectiles, music tracks, and node types used by the game.
- **`ResourceManager.h` / `ResourceManager.cpp`**  
  Game-specific resource loader using the engine’s `Cache.h`. Maps custom enum IDs to file paths.

### 5. Misc Files

- **`StateIdentifiers.h`**  
  Enumerates the game-specific states (Title, Menu, Game, Pause, etc.).
- **`SoundFxId.cpp`, `MusicId.cpp`, etc.**  
  Implementations or definitions for game-specific sound or music identifiers.

---

## Additional Notes on Systems

- **Engine** vs. **Game**:  
  The **Engine** code is designed to be generic and reusable. The **Game** namespace is a working example of how to use the engine. You can create your own `Game`-style folder to house custom gameplay logic while relying on the engine’s systems.

- **Scene Graph**:  
  The `WorldNode` (engine) is extended by game-specific nodes like `CanvasNode` or `Aircraft`. This layered approach keeps engine features general while allowing specialized game logic in separate classes.

- **Networking**:  
  The engine provides basic networking features (`NetworkNode`, partial states). The sample game shows a multiplayer state and server as examples of how to integrate network logic.

- **Resource Loading**:  
  The engine’s caching system is exposed via `Cache.h`. In the sample game, `ResourceManager.cpp` demonstrates how to map custom IDs (`TextureId`, `SoundFxId`) to file paths.

---