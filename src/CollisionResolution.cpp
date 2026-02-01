#include "physics/collision/CollisionResolution.h"

void CollisionResolution::ResolveCollision(RigidBody* a, RigidBody* b, const CollisionManifold& manifold) {
    resolveVelocity(a, b, manifold);
    resolvePosition(a, b, manifold);
}

void CollisionResolution::resolveVelocity(RigidBody* a, RigidBody* b, const CollisionManifold& manifold)
{
	float totalInvMass = a->getInvMass() + b->getInvMass();
	if (totalInvMass <= 0) return;

	Vector2 Vrel = a->getVelocity() - b->getVelocity();
	float Vnormal = Vrel.dotProduct(manifold.normal);

	if (Vnormal > 0) return;

	float e = std::min(a->getRestitution(), b->getRestitution());
	float j = (-(1 + e) * Vnormal) / totalInvMass;

	Vector2 impulse = manifold.normal * j;

	a->setVelocity(a->getVelocity() + impulse * a->getInvMass());
	b->setVelocity(b->getVelocity() - impulse * b->getInvMass());
}

void CollisionResolution::resolvePosition(RigidBody* a, RigidBody* b, const CollisionManifold& manifold)
{
	const float percent = 0.8f;
	const float slop = 0.01f;

	float totalInvMass = a->getInvMass() + b->getInvMass();
	if (totalInvMass <= 0) return;

	float correctionMagnitude = std::max(manifold.depth - slop, 0.0f) / totalInvMass * percent;
	Vector2 correction = manifold.normal * correctionMagnitude;

	a->setPosition(a->getPosition() + correction * a->getInvMass());
	b->setPosition(b->getPosition() - correction * b->getInvMass());
}