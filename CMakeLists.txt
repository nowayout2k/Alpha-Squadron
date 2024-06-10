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
        Source/Logger.cpp
        Header/Logger.h
        Header/Utility.h
        Header/LogType.h
        Header/Entity.h
        Header/SpriteEntity.h
        Source/Scene.cpp
        Header/Scene.h
        Source/Enemy.cpp
        Header/Enemy.h
        Source/WindowHandler.cpp
        Header/WindowHandler.h
        Source/Player.cpp
        Header/Player.h
        Source/ScrollingBackground.cpp
        Header/ScrollingBackground.h
        Header/SoundEffectType.h
        Header/MusicType.h
        Header/DrawableEntity.h
        Header/DrawableData.h
        Source/Bullet.cpp
        Header/Bullet.h
        Source/DataCache.cpp
        Header/DataCache.h
        Source/Character.cpp
        Header/Character.h
)

# Link the SFML libraries
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
