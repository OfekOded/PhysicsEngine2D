#pragma once
#include "math/Vector2.h"
#include "physics/shapes/Shape.h"
#include <memory>

class RigidBody {
private:
	float mass;
	float invMass;
	std::unique_ptr<Shape> shape;
	float rotation;
	Vector2 velocity;
	Vector2 position;
	Vector2 force;
	Vector2 acceleration;
	float damping;
	float restitution;
public:
	RigidBody(float m, std::unique_ptr<Shape> s, float r, float d = 1.0f, float res = 0.5f);

	void addForce(const Vector2& externalForce);

	void update(float deltaTime);

	const Vector2& getPosition() const;

	void setPosition(const Vector2& newPosition);

	float getMass() const;

	float getInvMass() const;

	const Vector2& getVelocity() const;

	void setVelocity(const Vector2& v);

	float getRestitution() const;

	const Shape* getShape() const;

	void setShape(std::unique_ptr<Shape> s);

	float getRotation() const;
};