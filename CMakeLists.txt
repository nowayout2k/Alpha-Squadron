cmake_minimum_required(VERSION 3.28)
project(SFML-Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add SFML MAC
#set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")

#Add SFML PC
set(SFML_DIR "C:/Users/Johnnie/Documents/SFML-2.6.1-VS/lib/cmake/SFML")

# Find the SFML package
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

add_executable(SFML-Core main.cpp
        Source/Audio.cpp
        Header/Audio.h
        Source/Graphics.cpp
        Header/Graphics.h
        Source/Network.cpp
        Header/Network.h
        Source/Input.cpp
        Header/Input.h
        Source/Entity.cpp
        Header/Entity.h
        Source/Logger.cpp
        Header/Logger.h
        Source/Utility.cpp
        Header/Utility.h
        Header/InputData.h
        Header/LogType.h
)

# Link the SFML libraries
target_link_libraries(SFML-Core sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
