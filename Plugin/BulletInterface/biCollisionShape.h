#pragma once

#include "biCommon.h"

extern "C"
{
	BI_EXPORT biCollisionShapeHandle biCreateBoxShape(biVector3 boxHalfExtents);
	BI_EXPORT void biDestroyCollisionShape(biCollisionShapeHandle collisionShapeHandle);
}
