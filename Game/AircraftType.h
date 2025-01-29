//
// Created by Johnnie Otis on 10/15/24.
//

#ifndef AIRCRAFTTYPE_H_
#define AIRCRAFTTYPE_H_

#include <string>

enum class AircraftType
{
	Chopper,
	Tomcat,
	Count
};

inline std::string AircraftTypeToString(AircraftType type)
{
	switch(type)
	{
	case AircraftType::Chopper:
		return "Chopper";
	case AircraftType::Tomcat:
		return "Tomcat";
	case AircraftType::Count:
		return "Count";
	default:
		return "NONE";
	}
}

#endif //AIRCRAFTTYPE_H_
