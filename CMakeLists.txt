cmake_minimum_required(VERSION 3.28)
project(Alpha-Squadron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent to manage nlohmann/json
include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.5  # Replace with the desired version
)

FetchContent_MakeAvailable(nlohmann_json)

# Add SFML MAC
#set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")

#Add SFML PC
set(SFML_DIR "C:/Users/Johnnie/Documents/SFML-2.6.1-VS/lib/cmake/SFML")

# Find the SFML package
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

add_executable(Alpha-Squadron main.cpp
        Source/Engine/Audio.cpp
        Headers/Engine/Audio.h
        Headers/Engine/Utility.h
        Headers/Engine/GameSprite.h
        Source/Game/World.cpp
        Headers/Engine/World.h
        Headers/Game/SoundFxId.h
        Headers/Game/MusicId.h
        Source/Game/Projectile.cpp
        Headers/Game/Projectile.h
        Source/Game/Aircraft.cpp
        Headers/Game/Aircraft.h
        Headers/Engine/GameText.h
        Headers/Engine/FontId.h
        Headers/Engine/Debug.h
        Source/Engine/Debug.cpp
        Source/Engine/Engine.cpp
        Headers/Engine/Engine.h
        Headers/Game/TextureId.h
        Source/Game/ResourceManager.cpp
        Headers/Game/ResourceManager.h
        Headers/Engine/Cache.h
        Headers/Engine/PooledSound.h
        Headers/Game/NodeType.h
        Source/Engine/WorldNode.cpp
        Headers/Engine/WorldNode.h
        Headers/Engine/Layer.h
        Headers/Engine/EmptyWorldNode.h
        Headers/Engine/Command.h
        Headers/Engine/CommandQueue.h
        Source/Game/Player.cpp
        Headers/Game/Player.h
        Source/Engine/StateStack.cpp
        Headers/Engine/StateStack.h
        Headers/Engine/State.h
        Headers/Game/StateIdentifiers.h
        Source/Game/GameState.cpp
        Headers/Game/GameState.h
        Source/Game/TitleState.cpp
        Headers/Game/TitleState.h
        Source/Game/MenuState.cpp
        Headers/Game/MenuState.h
        Source/Game/PauseState.cpp
        Headers/Game/PauseState.h
        Source/Engine/State.cpp
        Source/Engine/LoadingState.cpp
        Headers/Engine/LoadingState.h
        Source/Engine/ParallelTask.cpp
        Headers/Engine/ParallelTask.h
        Source/Engine/Component.cpp
        Headers/Engine/Component.h
        Source/Engine/Container.cpp
        Headers/Engine/Container.h
        Source/Engine/Label.cpp
        Headers/Engine/Label.h
        Source/Engine/Button.cpp
        Headers/Engine/Button.h
        Source/Game/SettingsState.cpp
        Headers/Game/SettingsState.h
        Headers/Game/DataTables.h
        Source/Game/DataTables.cpp
        Headers/Game/AircraftType.h
        Headers/Game/AiRoutine.h
        Headers/Game/Direction.h
        Source/Game/Pickup.cpp
        Headers/Game/Pickup.h
        Source/Game/GameOverState.cpp
        Headers/Game/GameOverState.h
        Headers/Engine/Particle.h
        Source/Engine/ParticleSystemNode.cpp
        Headers/Engine/ParticleSystemNode.h
        Source/Engine/EmitterNode.cpp
        Headers/Engine/EmitterNode.h
        Source/Engine/Animation.cpp
        Headers/Engine/Animation.h
        Source/Engine/PostEffect.cpp
        Headers/Engine/PostEffect.h
        Source/Engine/BloomEffect.cpp
        Headers/Engine/BloomEffect.h
        Headers/Engine/ShaderId.h
        Source/Game/CanvasNode.cpp
        Headers/Game/CanvasNode.h
        Source/Engine/GameSprite.cpp
        Headers/Engine/AudioNode.h
        Source/Game/MultiplayerGameState.cpp
        Headers/Game/MultiplayerGameState.h
        Source/Game/GameServer.cpp
        Headers/Game/GameServer.h
        Source/Engine/NetworkNode.cpp
        Headers/Engine/NetworkNode.h
        Headers/Engine/NetworkProtocol.h
        Source/Engine/KeyBinding.cpp
        Headers/Engine/KeyBinding.h
        Headers/Game/ParticleType.h
)

# Link the SFML libraries and nlohmann_json
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)
