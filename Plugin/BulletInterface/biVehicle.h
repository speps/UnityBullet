// WORK IN PROGRESS

#pragma once

#include "biCommon.h"

struct biVehicleTuning
{
	biScalar m_suspensionStiffness;
	biScalar m_suspensionCompression;
	biScalar m_suspensionDamping;
	biScalar m_maxSuspensionTravelCm;
	biScalar m_frictionSlip;
	biScalar m_maxSuspensionForce;

	biVehicleTuning()
		: m_suspensionStiffness(biScalar(5.88))
		, m_suspensionCompression(biScalar(0.83))
		, m_suspensionDamping(biScalar(0.88))
		, m_maxSuspensionTravelCm(biScalar(500.0))
		, m_frictionSlip(biScalar(10.5))
		, m_maxSuspensionForce(biScalar(6000.0))
	{
	}
};

struct biWheelRaycastInfo
{
	biVector3 m_contactNormalWS;
	biVector3 m_contactPointWS;
	biScalar m_suspensionLength;
	biVector3 m_hardPointWS;
	biVector3 m_wheelDirectionWS;
	biVector3 m_wheelAxleWS;
	bool m_isInContact;
	void* m_groundObject;
};

struct biWheelInfo
{
	biWheelRaycastInfo m_raycastInfo;
	biTransform m_worldTransform;
	biVector3 m_chassisConnectionPointCS; //const
	biVector3 m_wheelDirectionCS; //const
	biVector3 m_wheelAxleCS; // const or modified by steering
	biScalar m_suspensionRestLength1; //const
	biScalar m_maxSuspensionTravelCm;
	biScalar m_wheelsRadius; //const
	biScalar m_suspensionStiffness; //const
	biScalar m_wheelsDampingCompression; //const
	biScalar m_wheelsDampingRelaxation; //const
	biScalar m_frictionSlip;
	biScalar m_steering;
	biScalar m_rotation;
	biScalar m_deltaRotation;
	biScalar m_rollInfluence;
	biScalar m_maxSuspensionForce;
	biScalar m_engineForce;
	biScalar m_brake;
	bool m_bIsFrontWheel;
	void* m_clientInfo; //can be used to store pointer to sync transforms...
	biScalar m_clippedInvContactDotSuspension;
	biScalar m_suspensionRelativeVelocity;
	//calculated by suspension
	biScalar m_wheelsSuspensionForce;
	biScalar m_skidInfo;
};

extern "C"
{
	BI_EXPORT biVehicleHandle biCreateVehicle(biWorldHandle worldHandle, biVehicleTuning *tuning, biRigidBodyHandle chassisRigidBodyHandle);
	// CS is for "chassis space", relative to the chassis
	BI_EXPORT int biVehicleAddWheel(biVehicleHandle vehicleHandle, biVector3 connectionPointCS, biVector3 wheelDirectionCS,
		biVector3 wheelAxleCS, biScalar suspensionRestLength, biScalar wheelRadius, biVehicleTuning *tuning, bool isFrontWheel);
	BI_EXPORT void biVehicleGetWheelInfo(biVehicleHandle vehicleHandle, int wheelIndex, biWheelInfo *info);
	BI_EXPORT void biVehicleSetWheelInfo(biVehicleHandle vehicleHandle, int wheelIndex, const biWheelInfo *info);
	BI_EXPORT void biDestroyVehicle(biVehicleHandle vehicleHandle);
}
