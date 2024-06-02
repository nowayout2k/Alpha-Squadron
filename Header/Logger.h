//
// Created by Johnnie on 5/27/2024.
//

#ifndef ALPHA_SQUADRON_HEADER_LOGGER_H_
#define ALPHA_SQUADRON_HEADER_LOGGER_H_
#include "LogType.h"

class Logger
{
public:
    static void Log(LogType logType, const std::string& message);
};

#endif //ALPHA_SQUADRON_HEADER_LOGGER_H_
