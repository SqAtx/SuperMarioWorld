#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>
#include "Util.hpp"

namespace PhysicsConstants
{
	// Friction coefficients
	const float FrictionPlayerGound = 3.5;

	// Velocities
	const float PlayerMaxSpeed_Walk_X = 100;
	const float PlayerMaxSpeed_Run_X = 150;
	const float MinSpeed_X = 1;	// If character's speed is less than this, it's considered static

	// Accelerations
	const float Gravity = 100;
	const float PlayerAcc_Walk = 70;
	const float PlayerAcc_Run = 120;
}

#endif