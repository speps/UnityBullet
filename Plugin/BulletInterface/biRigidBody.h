#pragma once

#include "biCommon.h"

struct biRigidBodyConstructionInfo
{
	biScalar m_mass;
	biCollisionShapeHandle m_collisionShape;
	biScalar m_linearDamping;
	biScalar m_angularDamping;
	biScalar m_friction;
	biScalar m_rollingFriction;
	biScalar m_restitution;
	biScalar m_linearSleepingThreshold;
	biScalar m_angularSleepingThreshold;

	biRigidBodyConstructionInfo()
		: m_mass(biScalar(0.0))
		, m_collisionShape(0)
		, m_linearDamping(biScalar(0.0))
		, m_angularDamping(biScalar(0.0))
		, m_friction(biScalar(0.0))
		, m_rollingFriction(biScalar(0.0))
		, m_restitution(biScalar(0.0))
		, m_linearSleepingThreshold(biScalar(0.0))
		, m_angularSleepingThreshold(biScalar(0.0))
	{
	}
};

typedef void (__stdcall *biMotionStateGetTransform)(biUserData userData, biVector3 *outPosition, biQuaternion *outRotation);
typedef void (__stdcall *biMotionStateSetTransform)(biUserData userData, biVector3 inPosition, biQuaternion inRotation);

extern "C"
{
	BI_EXPORT biRigidBodyHandle biCreateRigidBody(biRigidBodyConstructionInfo *info, biUserData userData, biMotionStateGetTransform motionStateGet, biMotionStateSetTransform motionStateSet);
	BI_EXPORT biRigidBodyHandle biCreateRigidBodySimple(biRigidBodyConstructionInfo *info);
	BI_EXPORT void biDestroyRigidBody(biRigidBodyHandle rigidBodyHandle);

	BI_EXPORT void biActivateRigidBody(biRigidBodyHandle rigidBodyHandle);
}
