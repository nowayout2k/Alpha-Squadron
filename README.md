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
- [Additional Notes on Systems](#system-overview)
- [System Overview](#)

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

### System Overview
---
### Core Systems

The engine revolves around a few fundamental classes. These systems manage the
main loop, state transitions, and the scene graph. Together they keep the game
running smoothly.

#### GameEngine (Main Loop)

`GameEngine` sets up the window and drives the entire update cycle. Its `run()`
method repeatedly processes events, updates the active state, and renders the
scene:

```cpp
void GameEngine::run()
{
    sf::Clock clock;
    float timeStep = 0;

    while (m_window.isOpen())
    {
        timeStep += clock.restart().asSeconds();
        while (timeStep > TIME_STEP_MAX)
        {
            timeStep -= TIME_STEP_MAX;
            processEvents();
            if (!m_isPaused)
                update(sf::seconds(TIME_STEP_MAX));
        }
        render();
    }
}
```

#### StateStack (State Management)

`StateStack` maintains a stack of states such as menus or gameplay. New states
are registered with factory functions and pushed when needed:

```cpp
m_stateStack.registerState<AlphaSquadron::TitleState>(AlphaSquadron::StateId::Title);
m_stateStack.pushState(AlphaSquadron::StateId::Title);
```

It processes pending changes at the end of each frame so transitions occur
cleanly.

#### Scene Graph and Commands

Every drawable object derives from `WorldNode`. Nodes form a tree so commands
can traverse the graph and act on matching node types:

```cpp
void WorldNode::onCommand(const Command& command, sf::Time dt)
{
    if (command.NodeType & getNodeType())
        command.Action(*this, dt);
    for (auto& child : m_children)
        child->onCommand(command, dt);
}
```

This design keeps gameplay logic decoupled from the rendering hierarchy.


### State Management System

The engine organizes gameplay and menus using a stack of states. Every screen is
implemented as a class derived from `Engine::State`. The `Engine::StateStack`
handles which states are active and applies stack changes only after the current
update cycle.

#### Key Classes

```cpp
class State
{
public:
    using Ptr = std::unique_ptr<State>;

    virtual void render() = 0;
    virtual bool update(sf::Time deltaTime) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(AlphaSquadron::StateId stateId);
    void requestStackPop();
    void requestStateClear();
};
```

```cpp
class StateStack
{
public:
    void pushState(AlphaSquadron::StateId stateId);
    void popState();
    void clearStates();

    void update(sf::Time deltaTime);
    void render();
    void handleEvent(const sf::Event& event);
};
```

#### Registering and Transitioning States

States are registered with the stack when the engine starts:

```cpp
void GameEngine::registerStates()
{
    m_stateStack.registerState<AlphaSquadron::TitleState>(AlphaSquadron::StateId::Title);
    m_stateStack.registerState<AlphaSquadron::MenuState>(AlphaSquadron::StateId::Menu);
    // ...additional registrations...
}
```

Inside a state, you can request transitions:

```cpp
bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(StateId::Menu);
    }
    return true;
}
```


—

---

### Configuration System

The engine reads gameplay parameters from JSON files located in the `DataFiles` directory.
`DataTables.cpp` parses these files through the `AlphaSquadron::LoadData` function
which converts string values to engine enums using helpers from `Engine::Utility`.

An excerpt of `gameData.json` illustrates the layout:

```json
{
  "pickup": [
    {
      "type": "fire_spread",
      "value": 1,
      "textureId": "game_sprite_sheet",
      "textureLoadArea": { "left": 85, "top": 345, "width": 64, "height": 64 }
    }
  ]
}
```

At startup the world loads this file once:

```cpp
GameData World::GameData = LoadData("../DataFiles/gameData.json");
```

Components then access their settings via the returned `GameData` structure:

```cpp
const auto& info = World::GameData.AircraftData[AircraftType::Tomcat];
m_speed = info.Speed;
```

Editing the JSON allows you to tweak gameplay without recompiling the engine.


##### Game Data

The data for pickups, projectiles, particles, and aircraft is stored in
`DataFiles/gameData.json` and loaded at runtime. `DataTables.h` defines the
`GameData` structure that mirrors this JSON layout. At startup the world loads
the file with:

```cpp
GameData World::GameData = LoadData("../DataFiles/gameData.json");
```

Entities retrieve their settings from this global instance. For example, a
pickup uses its entry to configure textures and actions:

```cpp
auto dataPair = World::GameData.PickupData.find(m_pickupType);
if (dataPair != World::GameData.PickupData.end()) {
    auto data = dataPair->second;
    m_action = data.Action;
    setTextureId(data.TextureId);
    setTextureLoadArea(data.TextureLoadArea);
}
```

Particles access color and lifetime information in the same way:

```cpp
particle.Color = AlphaSquadron::World::GameData.ParticleData[m_type].Color;
particle.Lifetime = AlphaSquadron::World::GameData.ParticleData[m_type].Lifetime;
```

An excerpt from the JSON file illustrates the format:

```json
{
  "pickup": [
    {
      "textureId": "game_sprite_sheet",
      "textureLoadArea": { "left": 10, "top": 345, "width": 64, "height": 64 },
      "type": "health_refill",
      "value": 50
    }
  ]
}
```

By editing `gameData.json` you can tweak gameplay values or add new entries
without recompiling the code.

### Multiplayer System

The sample game showcases a simple client/server architecture built on top of SFML networking.
`GameServer` hosts the session while each client runs `MultiplayerGameState` to
sync gameplay over the network. When the state is created it tries to connect
to the host and either starts a server locally or connects as a client:

```cpp
// MultiplayerGameState.cpp
if (m_socket.connect(ip, Engine::ServerPort, sf::seconds(5.f)) == sf::TcpSocket::Done)
    m_connected = true;
else
    m_failedConnectionClock.restart();
```

During gameplay the state sends regular position updates for all local players:

```cpp
// MultiplayerGameState.cpp
sf::Packet positionUpdatePacket;
positionUpdatePacket << static_cast<sf::Int32>(Engine::Client::PositionUpdate);
positionUpdatePacket << static_cast<sf::Int32>(m_localPlayerIdentifiers.size());
for (sf::Int32 identifier : m_localPlayerIdentifiers)
{
    if (Aircraft* aircraft = m_world.getAircraft(identifier))
        positionUpdatePacket << identifier << aircraft->getPosition().x << aircraft->getPosition().y
                             << static_cast<sf::Int32>(aircraft->getHealth())
                             << static_cast<sf::Int32>(aircraft->getMissileCount());
}
m_socket.send(positionUpdatePacket);
```

On the server side, each incoming connection spawns a new aircraft and informs
all peers:

```cpp
// GameServer.cpp
if (m_listenerSocket.accept(m_peers[m_connectedPlayers]->Socket) == sf::TcpListener::Done)
{
    m_aircraftInfo[m_aircraftIdentifierCounter].Position =
        sf::Vector2f(m_battleFieldRect.left, m_battleFieldRect.height / 2);
    sf::Packet packet;
    packet << static_cast<sf::Int32>(Engine::Server::SpawnSelf)
           << m_aircraftIdentifierCounter
           << m_aircraftInfo[m_aircraftIdentifierCounter].Position.x
           << m_aircraftInfo[m_aircraftIdentifierCounter].Position.y;
    m_peers[m_connectedPlayers]->AircraftIdentifiers.push_back(m_aircraftIdentifierCounter);
    broadcastMessage("New player!");
    informWorldState(m_peers[m_connectedPlayers]->Socket);
    notifyPlayerSpawn(m_aircraftIdentifierCounter++);
    m_peers[m_connectedPlayers]->Socket.send(packet);
}
```

This protocol uses packet enums defined in `NetworkProtocol.h` for consistency.
The server relays realtime events and updates to keep every client in sync.


---
### UI System Walkthrough

The engine's GUI components form a small UI toolkit built entirely with SFML. Everything derives from `Engine::Component`, a drawable and transformable object that can respond to events. Higher level controls such as `Button` or `Label` implement this interface, while `Container` handles focus and event routing between child components.

#### Building a menu

To build a screen with interactive buttons you create a `Container` and pack components into it. The container listens for `W`/`S` or arrow keys to move selection and activates the currently selected widget on Return or Space.

```cpp
Engine::Container gui(*context.Audio);

auto playButton = std::make_shared<Engine::Button>(context);
playButton->setPosition(center.x, center.y - 100);
playButton->setText(20, "Play");
playButton->setCallback([this]() {
    requestStackPop();
    requestStackPush(StateId::Game);
});

gui.pack(playButton);
```

During rendering simply draw the container:

```cpp
window.draw(gui);
```

During event handling forward events to the container:

```cpp
bool MenuState::handleEvent(const sf::Event& event)
{
    m_guiContainer.handleEvent(event);
    return true;
}
```

This approach keeps UI logic separate from the state itself while making it easy to reuse widgets in other screens.


The `World` class orchestrates the entire scene. It builds a hierarchy of
`WorldNode` objects, each representing a layer such as background, sprite
front/back, particles, UI, and audio. Entities like `Aircraft` and `Pickup`
derive from `GameSprite` (which itself inherits from `WorldNode`) and are
attached to these layers. Every frame the world updates all nodes, resolves
collisions, spawns enemies, and scrolls the view.

An instance of `World` is created inside `GameState` and updated each frame:

```cpp
GameState::GameState(Engine::StateStack& stack, Context context)
    : State(stack, context),
      m_world(*context.Window, *context.Audio, false),
      m_player(nullptr, 1, context.KeysPlayer1)
{
    m_world.addAircraft(1, true); // Add the local player aircraft
}

bool GameState::update(sf::Time deltaTime)
{
    m_world.update(deltaTime);

    Engine::CommandQueue& commands = m_world.getCommandQueue();
    m_player.handleRealtimeInput(commands);
    return true;
}
```

Enemies or pickups can be spawned at any time using helper functions:

```cpp
m_world.addEnemy(AircraftType::Tomcat, 2500.f);              // Spawn an enemy
m_world.createPickUp({400.f, 200.f}, PickupType::HealthRefill); // Spawn a pickup
```

The world automatically integrates new objects into the scene graph and removes
them once they leave the battlefield bounds.

---
### Misc Features

The engine includes a few utility components that don't fit neatly into the core systems above. These features simplify common tasks such as asynchronous loading, logging and debugging, and resource caching.

#### ParallelTask

`ParallelTask` runs a function in a separate thread while reporting completion progress. It is typically used in the loading screen to avoid freezing the main loop.

```cpp
Engine::ParallelTask task;
task.execute([]()
{
    // Example long-running work
    loadResources();
});

while (!task.isFinished())
{
    float progress = task.getCompletion();
    updateProgressBar(progress);
}
```

#### Debug Utility

The `Debug` class prints log messages and can toggle developer overlays like the FPS counter or collider outlines.

```cpp
Engine::Debug::log("Window lost focus");
Engine::Debug::toggleFps();        // Show FPS counter
Engine::Debug::toggleDrawColliders();
```

#### Cache Template

`Cache` stores already loaded resources so subsequent requests return the same instance. The sample game uses it through `ResourceManager` but it can be used directly:

```cpp
Engine::Cache<sf::Texture> textureCache;

sf::Texture& player = textureCache.load("player", "../Assets/Textures/player.png");
// ... later requests with the same key return the cached texture
```

These helpers reduce boilerplate and keep the main engine systems focused on gameplay.

#### ParallelTask Example

The `ParallelTask` utility runs a function on a separate thread while the main
game loop stays responsive. A task can report its progress from inside the
thread and the owner can poll the state to drive a loading screen.

```cpp
Engine::ParallelTask loader;
loader.execute([&loader]() {
    for (unsigned i = 0; i < 10; ++i) {
        loadChunk(i);            // Perform part of the work
        loader.updateCompletion(0.1f);  // Report progress
    }
});

while (!loader.isFinished()) {
    float percent = loader.getCompletion();
    updateProgressBar(percent);
}
```


#### 8. Pooling System

The engine employs a small object pool for sound effects so that `sf::Sound`
instances are reused rather than created every time a sound plays. Each sound in
the pool is represented by the `PooledSound` structure:

```cpp
struct PooledSound
{
    sf::Sound Sound;
    bool IsAvailable = false;
};
```

When a new sound is requested, `Audio::getSoundFromPool()` first looks for an
available entry. If none are free, the pool grows until it reaches a preset
limit:

```cpp
PooledSound* Audio::getSoundFromPool()
{
    PooledSound* availableSound = nullptr;

    for (auto& pooledSound : m_sounds)
    {
        if (!pooledSound.IsAvailable && pooledSound.Sound.getStatus() == sf::Sound::Status::Stopped)
        {
            pooledSound.IsAvailable = true;
        }
    }

    for (auto& pooledSound : m_sounds)
    {
        if (pooledSound.IsAvailable)
        {
            availableSound = &pooledSound;
            break;
        }
    }

    if (!availableSound)
    {
        if (m_sounds.size() > POOL_RESIZE_LIMIT)
        {
            Engine::Debug::logWarning("Audio pool limit reached. Cannot play sound!");
            return nullptr;
        }
        m_sounds.emplace_back();
        availableSound = &m_sounds.back();
    }

    return availableSound;
}
```

After playback, a sound becomes available again when its status changes to
`Stopped`. This pooling strategy keeps memory allocations low and avoids the
overhead of repeatedly constructing sound objects during intense audio activity.


### Cache System

The `Cache` template in the engine provides a lightweight mechanism for loading
and reusing resources. Each cache stores objects of a specific type and indexes
them by a string key. When `load()` is called with a key, the cache first checks
if the resource already exists and returns it if so; otherwise it attempts to
load it from disk.

```cpp
// Stand-alone usage
Engine::Cache<sf::Texture> textureCache;
sf::Texture& tex = textureCache.load("ui-sheet", "../Assets/Textures/UI/ui_sprite_sheet.png");

// Loading a sub-rectangle using the parameter overload
sf::Texture& sub = textureCache.load(
    "ui-sheet-rect",
    "../Assets/Textures/UI/ui_sprite_sheet.png",
    sf::IntRect(0, 0, 64, 64));

// Subsequent calls with the same key return the cached instance
sf::Texture& same = textureCache.load("ui-sheet", "../Assets/Textures/UI/ui_sprite_sheet.png");

// Caches can be cleared when no longer needed
textureCache.clear();
```

In the sample game, `ResourceManager` wraps several cache instances to manage
textures, sounds, fonts and shaders. Clearing the state stack via
`StateStack::clear()` also calls `ResourceManager::clearAllCache()` to release
all cached assets.

- **`Cache.h`**
  Generic template used to load and cache resources. A resource is loaded once
  and retrieved by hash on subsequent calls.
- **`ResourceManager.h` / `ResourceManager.cpp`**
  Game-specific wrapper around `Cache` that maps enumeration IDs to file paths
  for textures, fonts, sound buffers and shaders.
- **`TextureId.h`**, **`SoundFxId.h`**, **`FontId.h`**, **`ShaderId.h`**
  Enumerations defining IDs used by `ResourceManager` to locate asset files.

Example usage:

```cpp
// Load a texture from the manager
sf::Texture& sheet = AlphaSquadron::ResourceManager::loadResource(
    AlphaSquadron::TextureId::UiSpriteSheet);

// Directly using the Cache template
Engine::Cache<sf::Texture> localCache;
sf::Texture& logo = localCache.load("logo", "../Assets/Textures/UI/company_logo.png");
```

The input system revolves around the **KeyBinding** class. Each player has a
set of actions mapped to keyboard keys. During the game loop, you poll the
`KeyBinding` instance to determine which actions are currently active and then
translate those actions into commands.

Example usage:

```cpp
// Create bindings for player one
Engine::KeyBinding playerInput(1);

// Inside your main event loop
sf::Event event;
while (window.pollEvent(event))
{
    // ... other event handling ...

    Engine::KeyBinding::ActionType action;
    if (playerInput.checkAction(event.key.code, action))
    {
        // Respond to the action (e.g., push a command)
    }
}

// Check realtime actions each frame
for (auto action : playerInput.getRealtimeActions())
{
    // Handle continuous input like movement or firing
}
```


### Audio System

The audio subsystem wraps SFML's sound API and provides a simple interface for
playing sound effects and music. The `Engine::Audio` class keeps a pool of
`sf::Sound` objects (`PooledSound`) so that multiple effects can play
simultaneously without frequent allocations. Sound buffers are loaded on demand
using `AlphaSquadron::ResourceManager` and each sound is positioned in 3D space
relative to the listener.

`AudioNode` connects this system with the scene graph. Entities can attach an
`AudioNode` and trigger audio from their world position. The listener position
is typically updated every frame to follow the player so positional audio
attenuates correctly.

#### Basic Usage

```cpp
#include "Headers/Engine/Audio.h"
#include "Headers/Engine/AudioNode.h"

Engine::Audio audio;
Engine::AudioNode soundNode(audio);

// Attach to the scene graph
worldGraph.attachNode(std::make_unique<Engine::AudioNode>(audio));

// Play a positional sound effect
soundNode.playSound(AlphaSquadron::SoundFxId::MissileLaunch,
                    sf::Vector2f(100.f, 200.f), 80.f);

// Start background music
audio.playMusic(AlphaSquadron::MusicId::GameMusic, 60.f);

// Update listener position each frame
sf::Vector2f listener = player.getWorldPosition();
Engine::Audio::setListenerPosition(listener);
```



##### Using the Animation Class

The `Animation` helper cycles through a sprite sheet based on the elapsed time. You
specify the size of each frame, the number of frames, and the overall duration of
the animation. Calling `update()` advances the animation and `draw()` renders the
current frame. Setting `setRepeating(true)` makes the animation loop.

```cpp
sf::Texture& sheet =
    AlphaSquadron::ResourceManager::loadResource(TextureId::ExplosionSpriteSheet);

Engine::Animation explosion(sheet, {256, 256}, 16, sf::seconds(1));
explosion.setPosition(100.f, 100.f);
explosion.setRepeating(false);

sf::Clock clock;
while (window.isOpen())
{
    sf::Time dt = clock.restart();
    explosion.update(dt);

    window.clear();
    window.draw(explosion);
    window.display();
}
```

This example creates an explosion animation that plays once when the aircraft is destroyed.


##### Example: Applying the Bloom Effect

The engine exposes a generic `PostEffect` interface with an `apply` method. The
`BloomEffect` class derives from it to create a glow around bright areas using a
series of shader passes. The simplified algorithm is:

```cpp
void BloomEffect::apply(const sf::RenderTexture& input, sf::RenderTarget& output)
{
    prepareTextures(input.getSize());
    filterBright(input, m_brightnessTexture);
    downSample(m_brightnessTexture, m_firstPassTextures[0]);
    blurMultipass(m_firstPassTextures);
    downSample(m_firstPassTextures[0], m_secondPassTextures[0]);
    blurMultipass(m_secondPassTextures);
    add(m_firstPassTextures[0], m_secondPassTextures[0], m_firstPassTextures[1]);
    m_firstPassTextures[1].display();
    add(input, m_firstPassTextures[1], output);
}
```

Within `World::render` the scene graph is drawn to an offscreen texture and the
effect is applied before the result is displayed:

```cpp
void World::render()
{
    if (!Engine::PostEffect::isSupported())
    {
        m_sceneTexture.clear();
        m_sceneTexture.setView(m_worldView);
        m_sceneTexture.draw(m_worldGraph);
        m_sceneTexture.display();
        m_bloomEffect.apply(m_sceneTexture, m_target);
    }
    else
    {
        m_target.setView(m_worldView);
        m_target.draw(m_worldGraph);
    }
}
```

This modular approach makes it easy to chain or swap effects while gracefully
handling systems without shader support.



---
### Scene Graph Overview

The engine organizes all world objects in a tree of `WorldNode` instances. Each node stores its children and a pointer to its parent. Transformations are propagated through this hierarchy, so moving a parent automatically moves all of its descendants. Updates and rendering follow the same pattern using `updateHierarchy()` and `renderState()`, meaning you only invoke these on the root node.

1. **Hierarchy management** – `attachNode()` adds a child and sets its parent. `detachNode()` removes it.
2. **World transforms** – `getWorldTransform()` walks up the parent chain to compute the full transform.
3. **Commands** – `onCommand()` dispatches actions from a `CommandQueue` to matching nodes based on their `NodeType` flags.

#### Example

```cpp
Engine::EmptyWorldNode root;

auto player = std::make_unique<AlphaSquadron::Aircraft>(
    AlphaSquadron::NodeType::Player,
    AlphaSquadron::AircraftType::Tomcat,
    sf::Vector2f(100.f, 100.f),
    sf::Vector2f(1.f, 1.f));

root.attachNode(std::move(player));
root.loadHierarchyResources();

// Game loop
root.updateHierarchy(deltaTime, commandQueue);
window.draw(root);
```


---
### Rendering System

The engine's rendering pipeline is built on top of **SFML** and revolves around
the `WorldNode` scene graph. Each node inherits from `WorldNode` and implements
`render()` for custom drawing. The hierarchical structure allows transforms to be
propagated to child nodes and keeps rendering organized.

At the highest level, `GameEngine::render()` clears the window, delegates the
draw calls to the active states, and finally displays the frame:

```cpp
void GameEngine::render()
{
    m_window.clear();
    m_stateStack.render();
    m_window.display();
}
```

Inside gameplay states, the `World` class handles offscreen rendering and post
effects. If post effects are available, the scene graph is drawn directly;
otherwise the scene is first rendered to a texture and processed (for example,
with bloom) before being drawn to the window:

```cpp
if (!Engine::PostEffect::isSupported())
{
    m_sceneTexture.clear();
    m_sceneTexture.setView(m_worldView);
    m_sceneTexture.draw(m_worldGraph);
    m_sceneTexture.display();
    m_bloomEffect.apply(m_sceneTexture, m_target);
}
else
{
    m_target.setView(m_worldView);
    m_target.draw(m_worldGraph);
}
```

To add visuals to the world, create nodes (such as `GameSprite`) and attach them
to the scene graph:

```cpp
auto spriteLayer = std::make_unique<Engine::EmptyWorldNode>();
auto player = std::make_unique<Engine::GameSprite>(TextureId::Player);
player->setPosition(100.f, 100.f);
spriteLayer->attachNode(std::move(player));
m_worldGraph.attachNode(std::move(spriteLayer));
```

The `WorldNode::renderState()` function recursively draws the node and all its
children, ensuring that each child inherits the transform of its parent. This
approach simplifies complex scenes and keeps updates and drawing separated.


##### Using the GUI Classes

The GUI system revolves around the `Component` base class. `Button`,
`Label`, and `Container` all derive from it. A `Container` manages focus
between child components and forwards input events to the currently
selected widget. Each `Button` can have a callback that executes when it
is activated.

Typical usage within a state looks like the following example. Buttons
are created, configured, and packed into a container. Events are then
forwarded to the container and the container is drawn in the state's
render method.

```cpp
Engine::Container gui(*context.Audio);

auto playButton = std::make_shared<Engine::Button>(context);
playButton->setText(30, "Play");
playButton->setCallback([this]() {
    requestStackPop();
    requestStackPush(StateId::Game);
});

gui.pack(playButton);

// inside State::handleEvent
gui.handleEvent(event);

// inside State::render
window.draw(gui);
```
