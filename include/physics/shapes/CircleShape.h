#pragma once
#include "Shape.h"
#include "physics/math/Vector2.h"

class CircleShape : public Shape {
private:
    float radius;

public:
    CircleShape(float r) : Shape(ShapeType::Circle), radius(r) {}

    float getRadius() const { return radius; }
    void setRadius(float r) { radius = r; }

    AABB getAABB(const Vector2& position, float rotation) const override {
        Vector2 extents(radius, radius);
        return AABB{ position - extents, position + extents };
    }
};