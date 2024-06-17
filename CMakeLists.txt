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
        Source/Audio.cpp
        Header/Audio.h
        Source/Network.cpp
        Header/Network.h
        Header/Utility.h
        Header/Entity.h
        Header/GameSprite.h
        Source/Scene.cpp
        Header/Scene.h
        Source/Helicopter.cpp
        Header/Helicopter.h
        Source/Jet.cpp
        Header/Jet.h
        Source/ScrollingBackground.cpp
        Header/ScrollingBackground.h
        Header/SoundFxId.h
        Header/MusicId.h
        Source/Projectile.cpp
        Header/Projectile.h
        Source/Character.cpp
        Header/Character.h
        Header/GameText.h
        Header/FontId.h
        Header/Debug.h
        Source/Debug.cpp
        Source/Game.cpp
        Header/Game.h
        Header/TextureId.h
        Source/ResourceManager.cpp
        Header/ResourceManager.h
        Header/Cache.h
        Header/IComponent.h
        Header/PooledSound.h
)

# Link the SFML libraries
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
