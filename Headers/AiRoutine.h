// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef AIROUTINE_H_
#define AIROUTINE_H_

/**
 * File: AiRoutine.h
 * Purpose: Defines the AiRoutine structure used for specifying AI movement routines.
 *
 * The AiRoutine structure contains an angle and a distance that represent the movement routine for an aircraft.
 */
struct AiRoutine
{
	/**
	 * Constructs an AiRoutine.
	 * @param angle The angle (in degrees) for the routine's direction.
	 * @param distance The distance to travel for this routine.
	 */
	AiRoutine(float angle, float distance) : Angle(angle), Distance(distance) {}

	float Angle;    ///< Angle in degrees for the routine's movement.
	float Distance; ///< Distance to travel for the routine.
};

#endif // AIROUTINE_H_
