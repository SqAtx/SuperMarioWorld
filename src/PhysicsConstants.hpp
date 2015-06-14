#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>
#include "Util.hpp"

namespace PhysicsConstants
{
	// Friction coefficients
	const float FrictionPlayerGound = 0.7;
	const float FrictionPlayerAir = 0.1;

	// Velocities
	const float PlayerMaxSpeed_Walk_X = 100;
	const float PlayerMaxSpeed_Run_X = 150;
	const float MinSpeed = 1;	// If character's speed is less than this on any axis, it's considered to be 0
	const float InitialYVelForJump = 160;
	const float MaxYVelForJump = 230;

	// Accelerations
	const float Gravity = 500;
	const float PlayerJumpAcc = -1250;
	const float PlayerAcc_Walk = 70;
	const float PlayerAcc_Run = 120;
}

#endif