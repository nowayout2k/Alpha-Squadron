cmake_minimum_required(VERSION 3.28)
project(Alpha-Squadron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add SFML MAC
#set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")

#Add SFML PC
set(SFML_DIR "C:/Users/Johnnie/Documents/SFML-2.6.1-VS/lib/cmake/SFML")

# Find the SFML package
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

add_executable(Alpha-Squadron main.cpp
        Engine/Audio.cpp
        Engine/Audio.h
        Engine/Network.cpp
        Engine/Network.h
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
        Engine/Input.cpp
        Engine/Input.h
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
)

# Link the SFML libraries
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
