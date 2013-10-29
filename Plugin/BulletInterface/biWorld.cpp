#include "biWorld.h"
#include "biCommonInternal.h"
#include "biRigidBodyInternal.h"

#include <btBulletDynamicsCommon.h>

struct biDynamicsWorldInternal
{
	btDynamicsWorld *m_world;
	btDispatcher *m_dispatcher;
	btBroadphaseInterface *m_broadphase;
	btConstraintSolver *m_solver;
	btCollisionConfiguration *m_configuration;
};

biWorldHandle biCreateDiscreteDynamicsWorld()
{
	biDynamicsWorldInternal *instance = new biDynamicsWorldInternal();
	instance->m_configuration = new btDefaultCollisionConfiguration();
	instance->m_dispatcher = new btCollisionDispatcher(instance->m_configuration);
	instance->m_broadphase = new btDbvtBroadphase();
	instance->m_solver = new btSequentialImpulseConstraintSolver();
	instance->m_world = new btDiscreteDynamicsWorld(
		instance->m_dispatcher,
		instance->m_broadphase,
		instance->m_solver,
		instance->m_configuration);
	return reinterpret_cast<biWorldHandle>(instance);
}

void biDestroyDiscreteDynamicsWorld(biWorldHandle worldHandle)
{
	biDynamicsWorldInternal *instance = reinterpret_cast<biDynamicsWorldInternal*>(worldHandle);
	delete instance->m_world;
	instance->m_world = 0;
	delete instance->m_solver;
	instance->m_solver = 0;
	delete instance->m_broadphase;
	instance->m_broadphase = 0;
	delete instance->m_dispatcher;
	instance->m_dispatcher = 0;
	delete instance->m_configuration;
	instance->m_configuration = 0;
}

void biAddRigidBody(biWorldHandle worldHandle, biRigidBodyHandle rigidBodyHandle)
{
	biDynamicsWorldInternal *instance = reinterpret_cast<biDynamicsWorldInternal*>(worldHandle);
	instance->m_world->addRigidBody(biGetRigidBody(rigidBodyHandle));
}

void biRemoveRigidBody(biWorldHandle worldHandle, biRigidBodyHandle rigidBodyHandle)
{
	biDynamicsWorldInternal *instance = reinterpret_cast<biDynamicsWorldInternal*>(worldHandle);
	instance->m_world->removeRigidBody(biGetRigidBody(rigidBodyHandle));
}

void biDynamicsWorldSetGravity(biWorldHandle worldHandle, biVector3 gravity)
{
	btVector3 btGravity;
	biConvert(gravity, btGravity);

	biDynamicsWorldInternal *instance = reinterpret_cast<biDynamicsWorldInternal*>(worldHandle);
	instance->m_world->setGravity(btGravity);
}

int biDynamicsWorldGetObjectsCount(biWorldHandle worldHandle)
{
	biDynamicsWorldInternal *instance = reinterpret_cast<biDynamicsWorldInternal*>(worldHandle);
	return instance->m_world->getNumCollisionObjects();
}

void biStepSimulation(biWorldHandle worldHandle, biScalar timeStep)
{
	biStepSimulation3(worldHandle, timeStep, 1, biScalar(1.0) / biScalar(60.0));
}

void biStepSimulation2(biWorldHandle worldHandle, biScalar timeStep, int maxSubSteps)
{
	biStepSimulation3(worldHandle, timeStep, maxSubSteps, biScalar(1.0) / biScalar(60.0));
}

void biStepSimulation3(biWorldHandle worldHandle, biScalar timeStep, int maxSubSteps, biScalar fixedTimeStep)
{
	biDynamicsWorldInternal *instance = reinterpret_cast<biDynamicsWorldInternal*>(worldHandle);
	instance->m_world->stepSimulation(timeStep, maxSubSteps, fixedTimeStep);
}

btDynamicsWorld* biGetWorld(biWorldHandle worldHandle)
{
	biDynamicsWorldInternal *instance = reinterpret_cast<biDynamicsWorldInternal*>(worldHandle);
	return instance->m_world;
}
