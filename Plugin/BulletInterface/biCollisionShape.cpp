#include "biCollisionShape.h"
#include "biCollisionShapeInternal.h"
#include "biCommonInternal.h"

#include <btBulletCollisionCommon.h>

struct biCollisionShapeInternal
{
	btCollisionShape *m_shape;
};

biCollisionShapeHandle biCreateBoxShape(biVector3 boxHalfExtents)
{
	biCollisionShapeInternal *instance = new biCollisionShapeInternal();
	btVector3 btBoxHalfExtents;
	biConvert(boxHalfExtents, btBoxHalfExtents);
	instance->m_shape = new btBoxShape(btBoxHalfExtents);
	return reinterpret_cast<biCollisionShapeHandle>(instance);
}

void biDestroyCollisionShape(biCollisionShapeHandle collisionShapeHandle)
{
	biCollisionShapeInternal *instance = reinterpret_cast<biCollisionShapeInternal*>(collisionShapeHandle);
	delete instance->m_shape;
	instance->m_shape = 0;
}



btCollisionShape* biGetCollisionShape(biCollisionShapeHandle collisionShapeHandle)
{
	biCollisionShapeInternal *instance = reinterpret_cast<biCollisionShapeInternal*>(collisionShapeHandle);
	return instance->m_shape;
}
