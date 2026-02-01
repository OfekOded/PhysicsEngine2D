#include "physics/World.h"
#include "physics/shapes/Shape.h"
#include "physics/shapes/BoxShape.h"
#include "physics/collision/CollisionDetection.h"
#include "physics/collision/CollisionResolution.h"
#include <algorithm>
#include <iostream>


World::World(Vector2 g) : gravity(g) {};

World::~World()
{
	for (const auto& body : bodies) 
		delete body;
}

void World::step(float deltaTime)
{
	for (const auto& body : bodies) {
		if(body->getMass() > 0)
			body->addForce(gravity * body->getMass());
		body->update(deltaTime);
	}
	collisionDetection();
}

void World::addBody(RigidBody* body)
{
	bodies.push_back(body);
}

void World::removeBody(RigidBody* body)
{
	auto it = std::find(bodies.begin(), bodies.end(), body);
	if (it != bodies.end()){
		delete *it;
		bodies.erase(it);
	}
}

void World::collisionDetection()
{
	for (size_t i = 0; i < bodies.size(); i++) {
		for (size_t j = i + 1; j < bodies.size(); j++) {
			RigidBody* bodyA = bodies[i];
			RigidBody* bodyB = bodies[j];

			CollisionManifold manifold;

			if (bodyA->getInvMass() == 0 && bodyB->getInvMass() == 0) continue;

			if (bodyA->getShape()->getType() == ShapeType::Circle &&
				bodyB->getShape()->getType() == ShapeType::Circle) {

				manifold = CollisionDetection::CircleVsCircle(bodyA, bodyB);
			}
		
			if (manifold.isColliding) {
				CollisionResolution::ResolveCollision(bodies[i], bodies[j], manifold);
			}
		}
	}
}