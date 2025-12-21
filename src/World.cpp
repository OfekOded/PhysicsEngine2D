#include "physics/World.h"
#include "physics/shapes/Shape.h"
#include "physics/shapes/BoxShape.h"
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
			float distance = bodies[i]->getPosition().distanceSquared(bodies[j]->getPosition());
			float sumRadii = bodies[i]->getRadius() + bodies[j]->getRadius();
			if (distance < sumRadii * sumRadii) {
				switch (bodies[i]->getShape()->getType()) {
				case ShapeType::Circle:
					if (bodies[j]->getShape()->getType() == ShapeType::Circle) {
						// קריאה לפונקציית Circle vs Circle
					}
					else if (bodies[j]->getShape()->getType() == ShapeType::Box) {
						// קריאה לפונקציית Circle vs Box
					}
					break;

				case ShapeType::Box:
					if (bodies[j]->getShape()->getType() == ShapeType::Circle) {
						// קריאה לפונקציית Circle vs Box (בסדר הפוך)
					}
					else if (bodies[j]->getShape()->getType() == ShapeType::Box) {
						// קריאה לפונקציית Box vs Box
					}
					break;
				}
			}
		}
	}
}

void World::resolveCollision(RigidBody* a, RigidBody* b)
{
	float distance = a->getPosition().distance(b->getPosition());
	float sumRadii = a->getRadius() + b->getRadius();
	float depth = sumRadii - distance;

	Vector2 normal = a->getPosition() - b->getPosition();
	if (normal.lengthSquared() == 0) {
		normal = Vector2(1, 0);
	}
	else {
		normal.normalize();
	}

	float totalInvMass = a->getInvMass() + b->getInvMass();
	if (totalInvMass <= 0) return;

	a->setPosition(a->getPosition() + (normal * depth) * (a->getInvMass() / totalInvMass));
	b->setPosition(b->getPosition() - (normal * depth) * (b->getInvMass() / totalInvMass));

	Vector2 Vrel = a->getVelocity() - b->getVelocity();
	float Vnormal = Vrel.dotProduct(normal);

	if (Vnormal > 0) return;

	float e = std::min(a->getRestitution(), b->getRestitution());
	float j = (-(1 + e) * Vnormal) / totalInvMass;

	a->setVelocity(a->getVelocity() + normal * (j * a->getInvMass()));
	b->setVelocity(b->getVelocity() - normal * (j * b->getInvMass()));
}



void CheckRectCollision(RigidBody* a, RigidBody* b) {
	BoxShape* shapeA = a->getShape();
	BoxShape* shapeB = b->getShape();

	float distanceX = std::abs(a->getPosition().x - b->getPosition().x);
	float overlapX = (shapeA->getWidth() + shapeB->getWidth()) / 2.0f - distanceX;

	float distanceY = std::abs(a->getPosition().y - b->getPosition().y);
	float overlapY = (shapeA->getHeight() + shapeB->getHeight()) / 2.0f - distanceY;

	if (overlapX > 0 && overlapY > 0) {
		Vector2 normal;
		if (overlapX < overlapY) {
			if (a->getPosition().x < b->getPosition().x) {
				normal = Vector2(-1, 0);
			}
			else {
				normal = Vector2(1, 0);
			}
		}
		else {
			if (a->getPosition().y < b->getPosition().y) {
				normal = Vector2(0, -1);
			}
			else {
				normal = Vector2(0, 1);
			}
		}
	}
}
