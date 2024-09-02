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
        Engine/Source/Audio.cpp
        Engine/Header/Audio.h
        Engine/Source/Network.cpp
        Engine/Header/Network.h
        Engine/Header/Utility.h
        Engine/Header/Entity.h
        Engine/Header/GameSprite.h
        Engine/Source/World.cpp
        Engine/Header/World.h
        Game/Source/Chopper.cpp
        Game/Header/Chopper.h
        Game/Source/Tomcat.cpp
        Game/Header/Tomcat.h
        Game/Header/SoundFxId.h
        Game/Header/MusicId.h
        Engine/Source/Projectile.cpp
        Engine/Header/Projectile.h
        Game/Source/Aircraft.cpp
        Game/Header/Aircraft.h
        Engine/Header/GameText.h
        Engine/Header/FontId.h
        Engine/Header/Debug.h
        Engine/Source/Debug.cpp
        Engine/Source/Game.cpp
        Engine/Header/Engine.h
        Game/Header/TextureId.h
        Engine/Source/ResourceManager.cpp
        Game/Header/ResourceManager.h
        Engine/Header/Cache.h
        Engine/Header/PooledSound.h
        Engine/Header/NodeType.h
        Engine/Source/WorldNode.cpp
        Engine/Header/WorldNode.h
        Engine/Header/Layer.h
        Engine/Header/EmptyWorldNode.h
        Engine/Header/Command.h
        Engine/Header/CommandQueue.h
        Engine/Source/Input.cpp
        Engine/Header/Input.h
        Engine/Source/StateStack.cpp
        Engine/Header/StateStack.h
)

# Link the SFML libraries
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
