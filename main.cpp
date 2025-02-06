// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "Headers/Engine.h"

#define BUILD_VERSION_MAJOR 0
#define BUILD_VERSION_MINOR 1
#define BUILD_VERSION_PATCH 0

int main()
{
	std::cout << "Build Version: "  << BUILD_VERSION_MAJOR << "."  << BUILD_VERSION_MINOR << "." << BUILD_VERSION_PATCH << std::endl;
	std::cout << "SFML Version: "  << SFML_VERSION_MAJOR << "."  << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;
	try
	{
		Engine engine;
		engine.run();
	}
	catch (std::exception& e)
	{
		std::cout << "EXCEPTION: " << e.what() << std::endl;
	}

    return 0;
}
