// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file main.cpp
 * @brief Entry point for the game engine.
 *
 * This file prints the build and SFML versions, instantiates the Engine,
 * and runs the main game loop. Any exceptions are caught and printed to the console.
 *
 * TODO: AUDIO AND PICKUPS FIX
 */

#include "Headers/Engine.h"

#define BUILD_VERSION_MAJOR 1
#define BUILD_VERSION_MINOR 0
#define BUILD_VERSION_PATCH 0

int main()
{
	// Output the build version.
	std::cout << "Build Version: "  << BUILD_VERSION_MAJOR << "."  << BUILD_VERSION_MINOR << "." << BUILD_VERSION_PATCH << std::endl;
	// Output the SFML version.
	std::cout << "SFML Version: "  << SFML_VERSION_MAJOR << "."  << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;
	try
	{
		// Create the Engine and run the main loop.
		Engine::GameEngine engine;
		engine.run();
	}
	catch (std::exception& e)
	{
		// Catch and report any exceptions thrown during execution.
		std::cout << "EXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}

//Structs and Enums
//definitions in headers to inline
//update Readme
// TODO: AUDIO AND PICKUPS and Multiplayer health bar fixes and Split into game and engine
