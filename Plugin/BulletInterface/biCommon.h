#pragma once

#ifdef BI_EXPORTS
	#define BI_EXPORT __declspec(dllexport)
#else
	#define BI_EXPORT __declspec(dllimport)
#endif

#define BI_DECLARE_HANDLE(name) typedef struct name##__ { int unused; } *name

BI_DECLARE_HANDLE(biWorldHandle);
BI_DECLARE_HANDLE(biRigidBodyHandle);
BI_DECLARE_HANDLE(biCollisionShapeHandle);
BI_DECLARE_HANDLE(biVehicleHandle);

#define BI_ATTRIBUTE_ALIGNED16(a) __declspec(align(16)) a

typedef void* biUserData;
typedef float biScalar;

struct biVector3
{
	biScalar m[3];

	biVector3()
	{
		m[0] = biScalar(0.0);
		m[1] = biScalar(0.0);
		m[2] = biScalar(0.0);
	}

	biVector3(biScalar x, biScalar y, biScalar z)
	{
		m[0] = x;
		m[1] = y;
		m[2] = z;
	}
};

struct biQuaternion
{
	biScalar m[4];

	biQuaternion()
	{
		m[0] = biScalar(0.0);
		m[1] = biScalar(0.0);
		m[2] = biScalar(0.0);
		m[3] = biScalar(1.0);
	}

	biQuaternion(biScalar x, biScalar y, biScalar z, biScalar w)
	{
		m[0] = x;
		m[1] = y;
		m[2] = z;
		m[3] = w;
	}
};

BI_ATTRIBUTE_ALIGNED16(struct) biMatrix3x3
{
	biVector3 m[3]; // row major
};

BI_ATTRIBUTE_ALIGNED16(struct) biTransform
{
	biMatrix3x3 m_basis; // rotation
	biVector3 m_origin; // position
};
