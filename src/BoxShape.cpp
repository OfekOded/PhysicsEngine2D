#include "physics/shapes/BoxShape.h"
#include <cmath>

std::array<Vector2, 4> BoxShape::getTransformedVertices(const Vector2& position, float rotation) const
{
    float c = std::cos(rotation);
    float s = std::sin(rotation);

    Vector2 axisX(c, s);
    Vector2 axisY(-s, c);

    return {
        position - axisX * halfWidth - axisY * halfHeight, // Top-Left
        position + axisX * halfWidth - axisY * halfHeight, // Top-Right
        position + axisX * halfWidth + axisY * halfHeight, // Bottom-Right
        position - axisX * halfWidth + axisY * halfHeight  // Bottom-Left
    };
}

AABB BoxShape::getAABB(const Vector2& position, float rotation) const {
    float s = std::sin(rotation);
    float c = std::cos(rotation);

    float newHalfWidth = std::abs(halfWidth * c) + std::abs(halfHeight * s);
    float newHalfHeight = std::abs(halfWidth * s) + std::abs(halfHeight * c);

    Vector2 newExtents(newHalfWidth, newHalfHeight);

    return AABB{ position - newExtents, position + newExtents };
}