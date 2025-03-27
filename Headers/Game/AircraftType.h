// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef AIRCRAFTTYPE_H_
#define AIRCRAFTTYPE_H_

#include <string>

namespace AlphaSquadron
{
	/**
	 * File: AircraftType.h
	 * Purpose: Defines the AircraftType enumeration used for identifying different aircraft types.
	 */
	enum class AircraftType
	{
		Chopper,             // Helicopter type aircraft.
		Tomcat,              // Fighter jet type aircraft.
		AircraftTypeCount    // Represents the count of aircraft types.
	};
}
#endif // AIRCRAFTTYPE_H_
