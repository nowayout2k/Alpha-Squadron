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
        Engine/Audio.cpp
        Engine/Audio.h
        Engine/Utility.h
        Engine/Entity.h
        Engine/GameSprite.h
        Engine/World.cpp
        Engine/World.h
        Game/Chopper.cpp
        Game/Chopper.h
        Game/Tomcat.cpp
        Game/Tomcat.h
        Game/SoundFxId.h
        Game/MusicId.h
        Engine/Projectile.cpp
        Engine/Projectile.h
        Game/Aircraft.cpp
        Game/Aircraft.h
        Engine/GameText.h
        Engine/FontId.h
        Engine/Debug.h
        Engine/Debug.cpp
        Engine/Engine.cpp
        Engine/Engine.h
        Game/TextureId.h
        Engine/ResourceManager.cpp
        Engine/ResourceManager.h
        Engine/Cache.h
        Engine/PooledSound.h
        Engine/NodeType.h
        Engine/WorldNode.cpp
        Engine/WorldNode.h
        Engine/Layer.h
        Engine/EmptyWorldNode.h
        Engine/Command.h
        Engine/CommandQueue.h
        Engine/Player.cpp
        Engine/Player.h
        Engine/StateStack.cpp
        Engine/StateStack.h
        Engine/State.h
        Engine/StateIdentifiers.h
        Engine/GameState.cpp
        Engine/GameState.h
        Engine/TitleState.cpp
        Engine/TitleState.h
        Engine/MenuState.cpp
        Engine/MenuState.h
        Engine/PauseState.cpp
        Engine/PauseState.h
        Engine/State.cpp
        Engine/LoadingState.cpp
        Engine/LoadingState.h
        Engine/ParallelTask.cpp
        Engine/ParallelTask.h
        Engine/Component.cpp
        Engine/Component.h
        Engine/Container.cpp
        Engine/Container.h
        Engine/Label.cpp
        Engine/Label.h
        Engine/Button.cpp
        Engine/Button.h
        Engine/SettingsState.cpp
        Engine/SettingsState.h
        Game/DataTables.h
        Game/DataTables.cpp
        Game/AircraftType.h
        Game/Direction.h
)

# Link the SFML libraries and nlohmann_json
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)
