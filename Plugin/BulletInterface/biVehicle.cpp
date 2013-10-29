#include "biVehicle.h"

#include "biCommonInternal.h"
#include "biWorldInternal.h"
#include "biRigidbodyInternal.h"

#include <btBulletDynamicsCommon.h>

struct biVehicleInternal
{
	btRaycastVehicle *m_vehicle;
	btVehicleRaycaster *m_raycaster;
};

void biConvert(biVehicleTuning* tuning, btRaycastVehicle::btVehicleTuning btTuning)
{
	btTuning.m_suspensionStiffness = tuning->m_suspensionStiffness;
	btTuning.m_suspensionCompression = tuning->m_suspensionCompression;
	btTuning.m_suspensionDamping = tuning->m_suspensionDamping;
	btTuning.m_maxSuspensionTravelCm = tuning->m_maxSuspensionTravelCm;
	btTuning.m_frictionSlip = tuning->m_frictionSlip;
	btTuning.m_maxSuspensionForce = tuning->m_maxSuspensionForce;
}

biVehicleHandle biCreateVehicle(biWorldHandle worldHandle, biVehicleTuning *tuning, biRigidBodyHandle chassisRigidBodyHandle)
{
	biVehicleInternal *instance = new biVehicleInternal();

	btRaycastVehicle::btVehicleTuning btTuning;
	biConvert(tuning, btTuning);

	instance->m_raycaster = new btDefaultVehicleRaycaster(biGetWorld(worldHandle));
	instance->m_vehicle = new btRaycastVehicle(btTuning, biGetRigidBody(chassisRigidBodyHandle), instance->m_raycaster);

	return reinterpret_cast<biVehicleHandle>(instance);
}

int biVehicleAddWheel(biVehicleHandle vehicleHandle, biVector3 connectionPointCS, biVector3 wheelDirectionCS,
		biVector3 wheelAxleCS, biScalar suspensionRestLength, biScalar wheelRadius, biVehicleTuning *tuning, bool isFrontWheel)
{
	btRaycastVehicle::btVehicleTuning btTuning;
	biConvert(tuning, btTuning);

	btVector3 btConnectionPointCS;
	biConvert(connectionPointCS, btConnectionPointCS);
	btVector3 btWheelDirectionCS;
	biConvert(wheelDirectionCS, btWheelDirectionCS);
	btVector3 btWheelAxleCS;
	biConvert(wheelAxleCS, btWheelAxleCS);

	biVehicleInternal *instance = reinterpret_cast<biVehicleInternal*>(vehicleHandle);
	instance->m_vehicle->addWheel(btConnectionPointCS, btWheelDirectionCS, btWheelAxleCS, suspensionRestLength, wheelRadius, btTuning, isFrontWheel);

	return instance->m_vehicle->getNumWheels() - 1;
}

void biVehicleGetWheelInfo(biVehicleHandle vehicleHandle, int wheelIndex, biWheelInfo *info)
{
	biVehicleInternal *instance = reinterpret_cast<biVehicleInternal*>(vehicleHandle);
	const btWheelInfo& btWheelInfoLocal = instance->m_vehicle->getWheelInfo(wheelIndex);

	{
		biConvert(btWheelInfoLocal.m_raycastInfo.m_contactNormalWS, info->m_raycastInfo.m_contactNormalWS);
		biConvert(btWheelInfoLocal.m_raycastInfo.m_contactPointWS, info->m_raycastInfo.m_contactPointWS);
		info->m_raycastInfo.m_suspensionLength = btWheelInfoLocal.m_raycastInfo.m_suspensionLength;
		biConvert(btWheelInfoLocal.m_raycastInfo.m_hardPointWS, info->m_raycastInfo.m_hardPointWS);
		biConvert(btWheelInfoLocal.m_raycastInfo.m_wheelDirectionWS, info->m_raycastInfo.m_wheelDirectionWS);
		biConvert(btWheelInfoLocal.m_raycastInfo.m_wheelAxleWS, info->m_raycastInfo.m_wheelAxleWS);
		info->m_raycastInfo.m_isInContact = btWheelInfoLocal.m_raycastInfo.m_isInContact;
		info->m_raycastInfo.m_groundObject = btWheelInfoLocal.m_raycastInfo.m_groundObject;
	}

	{
		biConvert(btWheelInfoLocal.m_worldTransform, info->m_worldTransform);
		biConvert(btWheelInfoLocal.m_chassisConnectionPointCS, info->m_chassisConnectionPointCS);
		biConvert(btWheelInfoLocal.m_wheelDirectionCS, info->m_wheelDirectionCS);
		biConvert(btWheelInfoLocal.m_wheelAxleCS, info->m_wheelAxleCS);
		info->m_suspensionRestLength1 = btWheelInfoLocal.m_suspensionRestLength1;
		info->m_maxSuspensionTravelCm = btWheelInfoLocal.m_maxSuspensionTravelCm;
		info->m_wheelsRadius = btWheelInfoLocal.m_wheelsRadius;
		info->m_suspensionStiffness = btWheelInfoLocal.m_suspensionStiffness;
		info->m_wheelsDampingCompression = btWheelInfoLocal.m_wheelsDampingCompression;
		info->m_wheelsDampingRelaxation = btWheelInfoLocal.m_wheelsDampingRelaxation;
		info->m_frictionSlip = btWheelInfoLocal.m_frictionSlip;
		info->m_steering = btWheelInfoLocal.m_steering;
		info->m_rotation = btWheelInfoLocal.m_rotation;
		info->m_deltaRotation = btWheelInfoLocal.m_deltaRotation;
		info->m_rollInfluence = btWheelInfoLocal.m_rollInfluence;
		info->m_maxSuspensionForce = btWheelInfoLocal.m_maxSuspensionForce;
		info->m_engineForce = btWheelInfoLocal.m_engineForce;
		info->m_brake = btWheelInfoLocal.m_brake;
		info->m_bIsFrontWheel = btWheelInfoLocal.m_bIsFrontWheel;
		info->m_clientInfo = btWheelInfoLocal.m_clientInfo;
		info->m_clippedInvContactDotSuspension = btWheelInfoLocal.m_clippedInvContactDotSuspension;
		info->m_suspensionRelativeVelocity = btWheelInfoLocal.m_suspensionRelativeVelocity;
		info->m_wheelsSuspensionForce = btWheelInfoLocal.m_wheelsSuspensionForce;
		info->m_skidInfo = btWheelInfoLocal.m_skidInfo;
	}
}

void biDestroyVehicle(biVehicleHandle vehicleHandle)
{
	biVehicleInternal *instance = reinterpret_cast<biVehicleInternal*>(vehicleHandle);
	delete instance->m_vehicle;
	instance->m_vehicle = 0;
	delete instance->m_raycaster;
	instance->m_raycaster = 0;
}
