#pragma once

#include "biCommon.h"

class btVector3;
class btQuaternion;
class btMatrix3x3;
class btTransform;

void biConvert(const biVector3& inV, btVector3& outV);
void biConvert(const biQuaternion& inQ, btQuaternion& outQ);
void biConvert(const biMatrix3x3& inQ, btMatrix3x3& outQ);
void biConvert(const biTransform& inT, btTransform& outT);

void biConvert(const btVector3& inV, biVector3& outV);
void biConvert(const btQuaternion& inQ, biQuaternion& outQ);
void biConvert(const btMatrix3x3& inM, biMatrix3x3& outM);
void biConvert(const btTransform& inT, biTransform& outT);

#define BI_STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1]
