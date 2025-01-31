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
        Audio.cpp
        Audio.h
        Utility.h
        Entity.h
        GameSprite.h
        World.cpp
        World.h
        Chopper.cpp
        Chopper.h
        Tomcat.cpp
        Tomcat.h
        SoundFxId.h
        MusicId.h
        Projectile.cpp
        Projectile.h
        Aircraft.cpp
        Aircraft.h
        GameText.h
        FontId.h
        Debug.h
        Debug.cpp
        Engine.cpp
        Engine.h
        TextureId.h
        ResourceManager.cpp
        ResourceManager.h
        Cache.h
        PooledSound.h
        NodeType.h
        WorldNode.cpp
        WorldNode.h
        Layer.h
        EmptyWorldNode.h
        Command.h
        CommandQueue.h
        Player.cpp
        Player.h
        StateStack.cpp
        StateStack.h
        State.h
        StateIdentifiers.h
        GameState.cpp
        GameState.h
        TitleState.cpp
        TitleState.h
        MenuState.cpp
        MenuState.h
        PauseState.cpp
        PauseState.h
        State.cpp
        LoadingState.cpp
        LoadingState.h
        ParallelTask.cpp
        ParallelTask.h
        Component.cpp
        Component.h
        Container.cpp
        Container.h
        Label.cpp
        Label.h
        Button.cpp
        Button.h
        SettingsState.cpp
        SettingsState.h
        DataTables.h
        DataTables.cpp
        AircraftType.h
        AiRoutine.h
        Direction.h
        Pickup.cpp
        Pickup.h
        GameOverState.cpp
        GameOverState.h
)

# Link the SFML libraries and nlohmann_json
target_link_libraries(Alpha-Squadron sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)
