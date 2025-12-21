#pragma once
#include "math/Vector2.h"
#include "RigidBody.h"
#include <vector>

class World {
private:
	std::vector<RigidBody*> bodies;
	Vector2 gravity;
public:
	World(Vector2 g = Vector2(0, -9.81));
	~World();

	void step(float deltaTime);
	void addBody(RigidBody* body);
	void removeBody(RigidBody* body);
	void collisionDetection();
	void resolveCollision(RigidBody* a, RigidBody* b);
};