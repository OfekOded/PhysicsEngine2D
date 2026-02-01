#pragma once
#include "physics/RigidBody.h"
#include "CollisionManifold.h"

class CollisionDetection {
public:
	static CollisionManifold CircleVsCircle(const RigidBody* a, const RigidBody* b);

	static CollisionManifold RectVsCircle(const RigidBody* a, const RigidBody* b);

	static CollisionManifold RectVsRect(const RigidBody* a, const RigidBody* b);
};