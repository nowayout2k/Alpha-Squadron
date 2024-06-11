//
// Created by Johnnie on 5/27/2024.
//

#include <iostream>
#include "../Header/Logger.h"

void Logger::log(LogType logType, const std::string& message)
{
    switch (logType)
    {
        case Error:
            std::cout << "ERROR: " << message << std::endl;
            break;
        case Verbose:
            std::cout << "LOG: " << message << std::endl;
            break;
        case Warning:
            std::cout << "WARNING: " << message << std::endl;
            break;
        case Test:
            std::cout << "TEST: " << message << std::endl;
            break;
    }
}