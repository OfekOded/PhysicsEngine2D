#include "physics\RigidBody.h"
#include "physics\math\Vector2.h"

RigidBody::RigidBody(float m, float r, float d, float res)
    : mass(m),
    radius(r),
    position(0.0f, 0.0f),
    velocity(0.0f, 0.0f),
    force(0.0f, 0.0f),
    acceleration(0.0f, 0.0f),
    damping(d),
    restitution(r) {
    if (mass == 0.0f) {
        invMass = 0.0f;
    }
    else {
        invMass = 1.0f / mass;
    }
}

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

float RigidBody::getRadius() const
{
    return radius;
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


