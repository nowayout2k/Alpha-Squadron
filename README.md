# Game Project

## Overview
This project is a game engine and framework designed to support the development of a game with various components like game states, entities, sound, and graphical elements. It includes support for managing game assets, entities, user input, and game states, as well as integrating audio and graphical features.

## Table of Contents
- [Components](#components)
- [Game States](#game-states)
- [Entities and Aircraft](#entities-and-aircraft)
- [Audio](#audio)
- [Utility](#utility)
- [Command System](#command-system)
- [Resource Management](#resource-management)
- [Data Tables](#data-tables)
- [Parallel Tasking](#parallel-tasking)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Components
The project includes several key components, such as:
- **GameSprite**: Handles sprite rendering and updates.
- **Label**: A UI component for displaying text.
- **Button**: A UI component for interactive buttons.
- **Container**: A container for UI elements, such as buttons and labels.
- **Layer**: Manages the layering of objects in the game scene.

## Game States
The game operates using various game states, which are managed by the **StateStack**:
- **TitleState**: The initial game screen where the player can start the game.
- **MenuState**: A state for handling the main menu.
- **PauseState**: Pauses the game and displays a pause screen.
- **GameOverState**: Displays when the game ends.
- **SettingsState**: Handles the settings menu for audio, graphics, and controls.

## Entities and Aircraft
The game includes various entities that can interact with each other, including:
- **Aircraft**: Base class for all aircraft types.
- **Player**: Represents the player in the game.
- **Tomcat** / **Chopper**: Specific types of aircraft in the game.
- **Pickup**: Represents pickups that the player can collect.
- **Projectile**: Represents projectiles fired in the game.

## Audio
The project has robust audio support:
- **SoundFxId**: Identifies sound effects used in the game.
- **MusicId**: Identifies background music tracks.
- **Audio**: Handles loading and playing sounds.
- **PooledSound**: Efficiently manages sound resources.

## Utility
Various utility files provide essential functions for the game:
- **Command**: Defines commands that can be executed during gameplay.
- **CommandQueue**: Manages the execution of commands.
- **Utility**: Provides helper functions for the game logic.

## Command System
The project includes a command system for managing user input and game events:
- **Command**: A basic command interface.
- **CommandQueue**: Stores and executes commands in sequence.

## Resource Management
Resources such as textures, fonts, and audio files are managed by:
- **ResourceManager**: Handles the loading and caching of game resources.
- **TextureId**: Identifies texture resources used in the game.
- **FontId**: Identifies font resources for text rendering.

## Data Tables
The project supports data-driven design through:
- **DataTables**: Holds static data for various game entities and objects.

## Parallel Tasking
The game supports parallel tasking for handling background processes:
- **ParallelTask**: Handles background tasks running in separate threads.

## Installation
To install and set up this project, clone the repository and follow these steps:
1. Ensure you have the required development tools (C++ compiler, libraries, etc.).
2. Set up your build system to compile the source files.

## Usage
Once installed, you can build and run the project through your preferred IDE or command line. The game engine will load the main menu, where you can start playing or adjust settings.

## License
This project is licensed under a proprietary license. You are not permitted to use, modify, or distribute the code without explicit permission from the author.

