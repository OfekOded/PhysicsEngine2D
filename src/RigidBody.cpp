#include "physics/RigidBody.h" 
#include "physics/math/Vector2.h"
#include <cmath> 

RigidBody::RigidBody(float m, std::unique_ptr<Shape> s, float r, float d, float res)
    : mass(m),
    invMass(mass == 0.0f ? 0.0f : 1.0f / mass), 
    shape(std::move(s)),
    rotation(r),         
    velocity(0.0f, 0.0f),
    position(0.0f, 0.0f),
    force(0.0f, 0.0f),
    acceleration(0.0f, 0.0f),
    damping(d),
    restitution(res)
{}

void RigidBody::addForce(const Vector2& externalForce) {
    force += externalForce;
}

void RigidBody::update(float deltaTime) {
    if (invMass <= 0.0f) return;

    acceleration = force * invMass;
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    velocity *= std::exp(-damping * deltaTime);
    force = Vector2(0.0f, 0.0f);
}

const Vector2& RigidBody::getPosition() const {
    return position;
}

void RigidBody::setPosition(const Vector2& newPosition)
{
    position = newPosition;
}

float RigidBody::getMass() const
{
    return mass;
}

float RigidBody::getInvMass() const
{
    return invMass;
}

const Vector2& RigidBody::getVelocity() const
{
    return velocity;
}

void RigidBody::setVelocity(const Vector2& v)
{
    velocity = v;
}

float RigidBody::getRestitution() const
{
    return restitution;
}

const Shape* RigidBody::getShape() const
{
    return shape.get();
}

void RigidBody::setShape(std::unique_ptr<Shape> s)
{
    shape = std::move(s);
}

float RigidBody::getRotation() const
{
    return rotation;
}


