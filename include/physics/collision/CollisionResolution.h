#pragma once 
#include "physics/RigidBody.h"
#include "CollisionManifold.h"

class CollisionResolution {
public:
	static void ResolveCollision(RigidBody* a, RigidBody* b, const CollisionManifold& manifold);

	static void resolveVelocity(RigidBody* a, RigidBody* b, const CollisionManifold& manifold);
	static void resolvePosition(RigidBody* a, RigidBody* b, const CollisionManifold& manifold);
};