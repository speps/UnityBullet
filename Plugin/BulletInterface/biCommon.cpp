#include "biCommon.h"

#include <btBulletCollisionCommon.h>

void biConvert(const biVector3& inV, btVector3& outV)
{
	outV = btVector3(btScalar(inV.m[0]), btScalar(inV.m[1]), btScalar(inV.m[2]));
}

void biConvert(const biQuaternion& inQ, btQuaternion& outQ)
{
	outQ = btQuaternion(btScalar(inQ.m[0]), btScalar(inQ.m[1]), btScalar(inQ.m[2]), btScalar(inQ.m[3]));
}

void biConvert(const biMatrix3x3& inM, btMatrix3x3& outM)
{
	biConvert(inM.m[0], outM[0]);
	biConvert(inM.m[1], outM[1]);
	biConvert(inM.m[2], outM[2]);
}

void biConvert(const biTransform& inT, btTransform& outT)
{
	btMatrix3x3 basis;
	biConvert(inT.m_basis, basis);
	outT.setBasis(basis);

	btVector3 origin;
	biConvert(inT.m_origin, origin);
	outT.setOrigin(origin);
}

void biConvert(const btVector3& inV, biVector3& outV)
{
	outV = biVector3(btScalar(inV.m_floats[0]), btScalar(inV.m_floats[1]), btScalar(inV.m_floats[2]));
}

void biConvert(const btQuaternion& inQ, biQuaternion& outQ)
{
	outQ = biQuaternion(btScalar(inQ.x()), btScalar(inQ.y()), btScalar(inQ.z()), btScalar(inQ.w()));
}

void biConvert(const btMatrix3x3& inM, biMatrix3x3& outM)
{
	biConvert(inM.getRow(0), outM.m[0]);
	biConvert(inM.getRow(1), outM.m[1]);
	biConvert(inM.getRow(2), outM.m[2]);
}

void biConvert(const btTransform& inT, biTransform& outT)
{
	biConvert(inT.getBasis(), outT.m_basis);
	biConvert(inT.getOrigin(), outT.m_origin);
}
