#pragma once
#include "../math/Vector2.h" 

struct CollisionManifold {
    bool isColliding;
    Vector2 normal;
    float depth;

    CollisionManifold()
        : isColliding(false), normal(0, 0), depth(0.0f) {
    }

    CollisionManifold(const Vector2& n, float d)
        : isColliding(true), normal(n), depth(d) {
    }
};