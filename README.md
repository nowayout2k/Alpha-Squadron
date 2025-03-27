# No Way Out Game Engine

Welcome to the No Way Out Game Engine! This project is a 2D game engine built using SFML. It is designed with modularity and flexibility in mind, allowing for robust single-player and networked multiplayer experiences. This README explains the project structure in detail, describing each major system, its components, and how they are implemented.

---

## Table of Contents

- [Overview](#overview)
- [Directory Structure](#directory-structure)
- [System Breakdown](#system-breakdown)
    - [Engine & Main Loop](#engine--main-loop)
    - [State Management](#state-management)
    - [World & Scene Graph](#world--scene-graph)
    - [Resource Management](#resource-management)
    - [Audio System](#audio-system)
    - [Visual Effects & Animation](#visual-effects--animation)
    - [Networking](#networking)
    - [GUI System](#gui-system)
    - [Input & Key Binding](#input--key-binding)
    - [Game Data & Configuration](#game-data--configuration)
    - [Utility & Debugging](#utility--debugging)
- [Building the Project](#building-the-project)
- [Contributing Guidelines](#contributing-guidelines)
- [Future Improvements](#future-improvements)

---

## Overview

The No Way Out Game Engine is structured to separate concerns and encapsulate functionality into distinct systems. Each system is implemented with flexibility and extensibility in mind, making it easy to contribute new features or modify existing ones. The major systems include:

- **Engine & Main Loop** – Manages window creation, event processing, and the main game loop.
- **State Management** – Implements a stack-based system for managing game states (Title, Menu, Game, Pause, etc.).
- **World & Scene Graph** – Manages the game world including rendering layers, collision detection, enemy spawning, and entity updates.
- **Resource Management** – Caches and loads assets such as textures, sounds, fonts, and shaders.
- **Audio System** – Plays sound effects and background music, and integrates with the scene graph via audio nodes.
- **Visual Effects & Animation** – Provides post-processing effects (e.g., bloom), particle systems, and frame-based animations.
- **Networking** – Handles multiplayer state, server communications, and networked game events.
- **GUI System** – Provides a set of components (buttons, labels, containers) to build user interfaces.
- **Input & Key Binding** – Manages key mappings and input handling for local player actions.
- **Game Data & Configuration** – Stores configuration data for various game elements loaded from external JSON files.
- **Utility & Debugging** – A collection of helper functions for mathematical operations, string manipulation, performance measurement, and logging.

---

## Directory Structure

- **Headers/**  
  Contains all header files that declare the classes, enumerations, and utility functions. Key headers include:
    - `Engine.h`: Defines the Engine class which runs the game loop.
    - `State.h`, `StateIdentifiers.h`: Define the abstract state class and its identifiers.
    - `StateStack.h`, `Command.h`, `CommandQueue.h`: Manage state transitions and command dispatching.
    - `World.h`: Manages the game world and its scene graph.
    - `WorldNode.h`: Base class for nodes in the scene graph.
    - `EmptyWorldNode.h`: Minimal node used for placeholder purposes.
    - `ResourceManager.h` & `Cache.h`: Handle resource loading and caching.
    - `Audio.h`, `AudioNode.h`: Implement the audio system.
    - `PostEffect.h`, `BloomEffect.h`: Provide post-processing effects.
    - `Animation.h`: Manages animations.
    - `MultiplayerGameState.h`, `GameServer.h`: Handle networking and multiplayer game state.
    - `GUI Components`: Includes `Component.h`, `Container.h`, `Button.h`, `Label.h`, `GameText.h` for building UIs.
    - `KeyBinding.h`: Manages key assignments and input mapping.
    - `DataTables.h`: Contains data structures for game configuration and a function to load them from JSON.
    - Other headers for enums and types such as `AircraftType.h`, `ProjectileType.h`, `PickupType.h`, `Particle.h`, `AiRoutine.h`, `Direction.h`, `Debug.h`, `ShaderId.h`, `SoundFxId.h`, `TextureId.h`, and `FontId.h`.

- **Source/**  
  Contains the implementation files (.cpp) for each of the header files.

- **Assets/**  
  Contains all game assets:
    - **Textures/**: Backgrounds, sprite sheets, UI elements, particles, etc.
    - **SFX/**: Sound effects.
    - **Fonts/**: Font files.
    - **Shaders/**: Shader files for post-processing.

- **DataFiles/**  
  Contains configuration files (e.g., JSON) for game data (aircraft, pickups, projectiles, particles).

---

## System Breakdown

### Engine & Main Loop

**Files:**
- `Engine.h`, `Engine.cpp`
- `main.cpp`

**Description:**
- The **Engine** class is the core of the application. It creates the SFML render window, instantiates the audio system, sets up key bindings, and initializes the state stack.
- The **main loop** in `Engine::run()` continuously processes events, updates the current state, and renders the frame. It ensures a smooth gameplay experience and proper resource cleanup.
- **Implementation Details:**
    - The Engine registers all states (Title, Menu, Game, Pause, Loading, etc.) with the StateStack.
    - It calls update, render, and processEvents in each loop iteration.

### State Management

**Files:**
- `State.h`, `State.cpp`
- `StateIdentifiers.h`
- `StateStack.h`, `StateStack.cpp`
- `Command.h`, `CommandQueue.h`

**Description:**
- **State**: An abstract base class for all game states, requiring each state to implement `render()`, `update()`, and `handleEvent()`.
- **StateIdentifiers**: Enumerates state IDs such as Title, Menu, Game, etc.
- **StateStack**: Manages active states using a stack. Supports deferred actions (push, pop, clear) and uses factory functions to instantiate states.
- **Command & CommandQueue**: Commands are dispatched to WorldNodes to trigger actions across the scene graph.
- **Implementation Details:**
    - States are pushed, popped, or cleared by adding a `PendingChange` to a list, which is applied after the current update cycle.
    - The Command system allows decoupling of event handling from state behavior.

### World & Scene Graph

**Files:**
- `World.h`, `World.cpp`
- `WorldNode.h`, `WorldNode.cpp`
- `EmptyWorldNode.h`
- `ParticleSystemNode.h`, `ParticleSystemNode.cpp`
- `CanvasNode.h`

**Description:**
- The **World** class encapsulates the entire game environment. It handles scrolling, enemy spawning, collision detection, and updating all world entities.
- **WorldNode** is the base class for all nodes in the scene graph. It supports hierarchical transformations, drawing, and collision checking.
- **EmptyWorldNode** is a minimal implementation for non-visible nodes.
- **ParticleSystemNode** handles particle effects, emitting particles based on configured properties.
- **CanvasNode** manages UI elements such as health bars.
- **Implementation Details:**
    - The scene graph is updated recursively by calling `updateHierarchy()` on the root node.
    - Collisions are detected by checking bounding rectangles of collidable nodes.
    - The world scrolls horizontally based on a defined scroll speed and applies post-processing effects like bloom.

### Resource Management

**Files:**
- `ResourceManager.h`, `ResourceManager.cpp`
- `Cache.h`

**Description:**
- The **ResourceManager** provides static methods to load and cache resources such as textures, sound buffers, fonts, and shaders.
- The **Cache** template class ensures that each resource is loaded only once and is reused across the project.
- **Implementation Details:**
    - Each resource is identified by a unique hash string (often a combination of file path and parameters).
    - If a resource is requested and already in the cache, it is returned immediately, otherwise, it is loaded from file.

### Audio System

**Files:**
- `Audio.h`, `Audio.cpp`
- `AudioNode.h`

**Description:**
- The **Audio** class manages playback of sound effects and music. It offers functions to play sounds at specific positions and to control music playback (play, pause, stop).
- The **AudioNode** integrates audio playback into the scene graph, allowing sounds to be played as part of the world.
- **Implementation Details:**
    - Audio positioning is based on the listener’s position (set via `sf::Listener`).
    - The audio system uses a sound pool (with the `PooledSound` structure) to reuse sound objects and minimize overhead.

### Visual Effects & Animation

**Files:**
- `PostEffect.h`
- `BloomEffect.h`, `BloomEffect.cpp`
- `Animation.h`
- `Particle.h`
- `AiRoutine.h`

**Description:**
- **PostEffect** is an abstract class for applying post-processing effects.
- **BloomEffect** implements a bloom effect using multiple render textures, brightness filtering, down sampling, and Gaussian blur.
- **Animation** manages frame-based animations and supports features like looping and explosion animations.
- **Particles** and **AiRoutine** define the behavior of particle effects and AI movement patterns.
- **Implementation Details:**
    - The bloom effect is applied by rendering the scene to an off-screen texture, processing it with multiple passes, and blending it back to the main target.
    - Animations are updated based on elapsed time and frame count, and can be triggered to restart or repeat.

### Networking

**Files:**
- `MultiplayerGameState.h`, `MultiplayerGameState.cpp`
- `GameServer.h`, `GameServer.cpp`

**Description:**
- **MultiplayerGameState** handles the multiplayer game state, including network communication, updating the world from server packets, and managing client connections.
- **GameServer** is responsible for handling incoming connections, processing packets, broadcasting game events, and managing client state.
- **Implementation Details:**
    - The multiplayer state sets up a TCP connection and uses SFML’s networking features to send/receive packets.
    - Server-side logic manages peer connections, handles timeouts, and synchronizes game state across clients.

### GUI System

**Files:**
- `Component.h`
- `Container.h`
- `Button.h`
- `Label.h`
- `GameText.h`

**Description:**
- The GUI system is built using a composite pattern:
    - **Component** is the base class for all GUI elements.
    - **Container** manages a collection of components, handling navigation and event forwarding.
    - **Button** is an interactive component that triggers callbacks on activation.
    - **Label** is a non-interactive component for displaying text.
    - **GameText** is a WorldNode that displays text within the game world.
- **Implementation Details:**
    - Components are drawn with SFML's Drawable interface and transformed using Transformable.
    - Containers allow selection and toggling of child components to build interactive menus.

### Input & Key Binding

**Files:**
- `KeyBinding.h`

**Description:**
- **KeyBinding** manages the mapping of SFML key codes to in-game actions for local players.
- It supports assigning keys, checking for active realtime actions, and retrieving key assignments.
- **Implementation Details:**
    - Key bindings are stored in a map.
    - A helper function `IsRealtimeAction` determines whether an action should be handled continuously.
    - Realtime input is processed by checking the current state of keys and dispatching corresponding actions.

### Game Data & Configuration

**Files:**
- `DataTables.h`

**Description:**
- Contains data structures (e.g., `AircraftData`, `PickupData`, `ProjectileData`, `ParticleData`) to configure various game entities.
- Provides the `LoadData` function to load game configuration from JSON files.
- **Implementation Details:**
    - Game data is organized into maps keyed by enums (e.g., AircraftType, PickupType).
    - These tables are used during resource loading and entity initialization to set properties like health, speed, textures, and AI routines.

### Utility & Debugging

**Files:**
- `Utility.h`
- `Debug.h`

**Description:**
- **Utility** is a collection of static helper functions for mathematics (vector normalization, magnitude, lerp), angle conversion (to/from radians), random number generation, string manipulation, and input key conversion.
- **Debug** provides logging functionality and toggles for debugging features like FPS display and collider visualization.
- **Implementation Details:**
    - Utility functions are used throughout the project to reduce code duplication and enforce consistency.
    - Debug functions conditionally log messages based on a global debugging flag.

---