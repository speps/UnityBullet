#pragma once

#include "biCommon.h"

extern "C"
{
	BI_EXPORT biWorldHandle biCreateDiscreteDynamicsWorld();
	BI_EXPORT void biDestroyDiscreteDynamicsWorld(biWorldHandle worldHandle);

	BI_EXPORT void biAddRigidBody(biWorldHandle worldHandle, biRigidBodyHandle rigidBodyHandle);
	BI_EXPORT void biRemoveRigidBody(biWorldHandle worldHandle, biRigidBodyHandle rigidBodyHandle);

	BI_EXPORT void biDynamicsWorldSetGravity(biWorldHandle worldHandle, biVector3 gravity);
	BI_EXPORT int biDynamicsWorldGetObjectsCount(biWorldHandle worldHandle);

	BI_EXPORT void biStepSimulation(biWorldHandle worldHandle, biScalar timeStep);
	BI_EXPORT void biStepSimulation2(biWorldHandle worldHandle, biScalar timeStep, int maxSubSteps);
	BI_EXPORT void biStepSimulation3(biWorldHandle worldHandle, biScalar timeStep, int maxSubSteps, biScalar fixedTimeStep);
}
