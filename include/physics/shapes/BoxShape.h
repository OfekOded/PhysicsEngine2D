#pragma once
#include "Shape.h"
#include "physics/math/Vector2.h"
#include <array>

class BoxShape : public Shape {
private:
    float halfWidth;
    float halfHeight;

public:
    BoxShape(float width, float height)
        : Shape(ShapeType::Box), halfWidth(width * 0.5f), halfHeight(height * 0.5f) {
    }

    float getWidth() const { return halfWidth * 2.0f; }
    float getHeight() const { return halfHeight * 2.0f; }

    void setWidth(float w) { halfWidth = w * 0.5f; }
    void setHeight(float h) { halfHeight = h * 0.5f; }

    float getHalfWidth() const { return halfWidth; }
    float getHalfHeight() const { return halfHeight; }

    std::array<Vector2, 4> getTransformedVertices(const Vector2& position, float rotation) const;
    AABB getAABB(const Vector2& position, float rotation) const override;
};