#include "biRigidBody.h"

#include "biCommonInternal.h"
#include "biCollisionShapeInternal.h"

#include <btBulletDynamicsCommon.h>

struct biRigidBodyInternal
{
	btRigidBody *m_rigidBody;
	btMotionState *m_motionState;
};

class biCallbackMotionState : public btMotionState
{
private:
	biUserData m_userData;
	biMotionStateGetTransform m_getTransform;
	biMotionStateSetTransform m_setTransform;

public:
	biCallbackMotionState(biUserData userData, biMotionStateGetTransform get, biMotionStateSetTransform set)
		: m_userData(userData)
		, m_getTransform(get)
		, m_setTransform(set)
	{
		
	}

	virtual void getWorldTransform(btTransform& centerOfMassWorldTrans) const
	{
		biVector3 outPosition;
		biQuaternion outRotation;
		m_getTransform(m_userData, &outPosition, &outRotation);

		btVector3 btPosition;
		biConvert(outPosition, btPosition);
		btQuaternion btRotation;
		biConvert(outRotation, btRotation);

		centerOfMassWorldTrans = btTransform(btRotation, btPosition);
	}

	virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans)
	{
		biVector3 position;
		biConvert(centerOfMassWorldTrans.getOrigin(), position);
		biQuaternion rotation;
		biConvert(centerOfMassWorldTrans.getRotation(), rotation);

		m_setTransform(m_userData, position, rotation);
	}
};

biRigidBodyHandle biCreateRigidBodySimple(biRigidBodyConstructionInfo *info)
{
	biRigidBodyInternal *instance = new biRigidBodyInternal();
	instance->m_motionState = new btDefaultMotionState();

	btCollisionShape *shape = biGetCollisionShape(info->m_collisionShape);
	btVector3 localInertia;
	shape->calculateLocalInertia(info->m_mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo btInfo(info->m_mass, instance->m_motionState, shape);
	btInfo.m_localInertia = localInertia;
	btInfo.m_linearDamping = info->m_linearDamping;
	btInfo.m_angularDamping = info->m_angularDamping;
	btInfo.m_friction = info->m_friction;
	btInfo.m_rollingFriction = info->m_rollingFriction;
	btInfo.m_restitution = info->m_restitution;
	btInfo.m_linearSleepingThreshold = info->m_linearSleepingThreshold;
	btInfo.m_angularSleepingThreshold = info->m_angularSleepingThreshold;

	instance->m_rigidBody = new btRigidBody(btInfo);

	return reinterpret_cast<biRigidBodyHandle>(instance);
}

biRigidBodyHandle biCreateRigidBody(biRigidBodyConstructionInfo *info, biUserData userData, biMotionStateGetTransform motionStateGet, biMotionStateSetTransform motionStateSet)
{
	biRigidBodyInternal *instance = new biRigidBodyInternal();
	instance->m_motionState = new biCallbackMotionState(userData, motionStateGet, motionStateSet);

	btCollisionShape *shape = biGetCollisionShape(info->m_collisionShape);
	btVector3 localInertia;
	shape->calculateLocalInertia(info->m_mass, localInertia);

	btRigidBody::btRigidBodyConstructionInfo btInfo(info->m_mass, instance->m_motionState, shape);
	btInfo.m_localInertia = localInertia;
	btInfo.m_linearDamping = info->m_linearDamping;
	btInfo.m_angularDamping = info->m_angularDamping;
	btInfo.m_friction = info->m_friction;
	btInfo.m_rollingFriction = info->m_rollingFriction;
	btInfo.m_restitution = info->m_restitution;
	btInfo.m_linearSleepingThreshold = info->m_linearSleepingThreshold;
	btInfo.m_angularSleepingThreshold = info->m_angularSleepingThreshold;

	instance->m_rigidBody = new btRigidBody(btInfo);

	return reinterpret_cast<biRigidBodyHandle>(instance);
}

void biDestroyRigidBody(biRigidBodyHandle rigidBodyHandle)
{
	biRigidBodyInternal *instance = reinterpret_cast<biRigidBodyInternal*>(rigidBodyHandle);
	delete instance->m_rigidBody;
	instance->m_rigidBody = 0;
	delete instance->m_motionState;
	instance->m_motionState = 0;
}

void biActivateRigidBody(biRigidBodyHandle rigidBodyHandle)
{
	biRigidBodyInternal *instance = reinterpret_cast<biRigidBodyInternal*>(rigidBodyHandle);
	instance->m_rigidBody->activate();
}

btRigidBody* biGetRigidBody(biRigidBodyHandle rigidBodyHandle)
{
	biRigidBodyInternal *instance = reinterpret_cast<biRigidBodyInternal*>(rigidBodyHandle);
	return instance->m_rigidBody;
}
