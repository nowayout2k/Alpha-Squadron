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

add_executable(Alpha-Squadron Source/main.cpp
        Source/Audio.cpp
        Headers/Audio.h
        Headers/Utility.h
        Headers/Entity.h
        Headers/GameSprite.h
        Source/World.cpp
        Headers/World.h
        Source/Chopper.cpp
        Headers/Chopper.h
        Source/Tomcat.cpp
        Headers/Tomcat.h
        Headers/SoundFxId.h
        Headers/MusicId.h
        Source/Projectile.cpp
        Headers/Projectile.h
        Source/Aircraft.cpp
        Headers/Aircraft.h
        Headers/GameText.h
        Headers/FontId.h
        Headers/Debug.h
        Source/Debug.cpp
        Source/Engine.cpp
        Headers/Engine.h
        Headers/TextureId.h
        Source/ResourceManager.cpp
        Headers/ResourceManager.h
        Headers/Cache.h
        Headers/PooledSound.h
        Headers/NodeType.h
        Source/WorldNode.cpp
        Headers/WorldNode.h
        Headers/Layer.h
        Headers/EmptyWorldNode.h
        Headers/Command.h
        Headers/CommandQueue.h
        Source/Player.cpp
        Headers/Player.h
        Source/StateStack.cpp
        Headers/StateStack.h
        Headers/State.h
        Headers/StateIdentifiers.h
        Source/GameState.cpp
        Headers/GameState.h
        Source/TitleState.cpp
        Headers/TitleState.h
        Source/MenuState.cpp
        Headers/MenuState.h
        Source/PauseState.cpp
        Headers/PauseState.h
        Source/State.cpp
        Source/LoadingState.cpp
        Headers/LoadingState.h
        Source/ParallelTask.cpp
        Headers/ParallelTask.h
        Source/Component.cpp
        Headers/Component.h
        Source/Container.cpp
        Headers/Container.h
        Source/Label.cpp
        Headers/Label.h
        Source/Button.cpp
        Headers/Button.h
        Source/SettingsState.cpp
        Headers/SettingsState.h
        Headers/DataTables.h
        Source/DataTables.cpp
        Headers/AircraftType.h
        Headers/AiRoutine.h
        Headers/Direction.h
        Source/Pickup.cpp
        Headers/Pickup.h
        Source/GameOverState.cpp
        Headers/GameOverState.h
)

# Link the SFML libraries and nlohmann_json
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)
