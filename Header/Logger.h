//
// Created by Johnnie on 5/27/2024.
//

#ifndef SFML_CORE_HEADER_LOGGER_H_
#define SFML_CORE_HEADER_LOGGER_H_
#include "LogType.h"

namespace SfmlCoreUtility
{
	class Logger
	{

	 public:
		static void Log(LogType logType, const std::string& message);
	};
}

#endif //SFML_CORE_HEADER_LOGGER_H_
