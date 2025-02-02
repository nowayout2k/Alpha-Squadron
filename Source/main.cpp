// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/Engine.h"

int main()
{
	try
	{
		Engine engine;
		engine.run();
	}
	catch (std::exception& e)
	{
		std::cout << "
EXCEPTION: " << e.what() << std::endl;
	}

    return 0;
}
