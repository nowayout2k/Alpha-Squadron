cmake_minimum_required(VERSION 3.28)
project(SFMLTemplate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add SFML
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

add_executable(SFMLTemplate main.cpp
        Source/Audio.cpp
        Header/Audio.h
        Source/Graphics.cpp
        Header/Graphics.h
        Source/Network.cpp
        Header/Network.h
        Source/Input.cpp
        Header/Input.h
        Source/Entity.cpp
        Header/Entity.h)

target_link_libraries(SFMLTemplate sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
