#include "Engine/Header/Engine.h"

int main()
{
	try
	{
		Engine engine;
		engine.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

    return 0;
}
