#include "physics/collision/CollisionDetection.h"
#include "physics/shapes/CircleShape.h"
#include "physics/shapes/BoxShape.h"
#include <vector>
#include <cmath>


CollisionManifold CollisionDetection::CircleVsCircle(const RigidBody* a, const RigidBody* b)
{
    const CircleShape* circleA = static_cast<const CircleShape*>(a->getShape());
    const CircleShape* circleB = static_cast<const CircleShape*>(b->getShape());

    Vector2 normal = a->getPosition() - b->getPosition();
    float sumRadius = circleA->getRadius() + circleB->getRadius();
    float distSq = normal.lengthSquared();

    if (distSq >= sumRadius * sumRadius)
        return CollisionManifold();

    float distance = std::sqrt(distSq);

    if (distance == 0.0f)
    {
        return CollisionManifold(Vector2(0, 1), sumRadius);
    }

    return CollisionManifold(normal / distance, sumRadius - distance);
}

CollisionManifold CollisionDetection::RectVsCircle(const RigidBody* a, const RigidBody* b)
{
    const CircleShape* circleA = static_cast<const CircleShape*>(a->getShape());
    const BoxShape* rectB = static_cast<const BoxShape*>(b->getShape());

    Vector2 circlePos = a->getPosition();
    Vector2 boxPos = b->getPosition();
    float boxAngle = b->getRotation();

    Vector2 dir = circlePos - boxPos;
    float c = std::cos(-boxAngle);
    float s = std::sin(-boxAngle);
    Vector2 localPos(dir.x * c - dir.y * s, dir.x * s + dir.y * c);

    float halfW = rectB->getHalfWidth();
    float halfH = rectB->getHalfHeight();

    float closestX = std::max(-halfW, std::min(localPos.x, halfW));
    float closestY = std::max(-halfH, std::min(localPos.y, halfH));

    Vector2 localDiff = localPos - Vector2(closestX, closestY);
    float distSq = localDiff.lengthSquared();
    float radius = circleA->getRadius();

    if (distSq > radius * radius)
    {
        return CollisionManifold();
    }

    float distance = std::sqrt(distSq);
    Vector2 normal;

    if (distance == 0.0f)
    {
        normal = Vector2(0, 1);
    }
    else
    {
        Vector2 localNormal = localDiff / distance;
        float c2 = std::cos(boxAngle);
        float s2 = std::sin(boxAngle);
        normal = Vector2(localNormal.x * c2 - localNormal.y * s2, localNormal.x * s2 + localNormal.y * c2);
    }

    return CollisionManifold(normal, radius - distance);
}

CollisionManifold CollisionDetection::RectVsRect(const RigidBody* a, const RigidBody* b)
{
    const BoxShape* rectA = static_cast<const BoxShape*>(a->getShape());
    const BoxShape* rectB = static_cast<const BoxShape*>(b->getShape());

    float boxAngleA = a->getRotation();
    float boxAngleB = b->getRotation();

    float cA = std::cos(boxAngleA);
    float sA = std::sin(boxAngleA);
    float cB = std::cos(boxAngleB);
    float sB = std::sin(boxAngleB);

    std::vector<Vector2> verticesA;
    verticesA.reserve(4);

    Vector2 normalHeightA(rectA->getHalfHeight()*-sA, rectA->getHalfHeight()*cA);
    Vector2 normalWidthA(rectA->getHalfWidth()*cA, rectA->getHalfWidth()*sA);
    Vector2 centerA = a->getPosition();

    verticesA.emplace_back(centerA + normalHeightA + normalWidthA);
    verticesA.emplace_back(centerA - normalHeightA + normalWidthA);
    verticesA.emplace_back(centerA + normalHeightA - normalWidthA);
    verticesA.emplace_back(centerA - normalHeightA - normalWidthA);

    std::vector<Vector2> verticesB;
    verticesB.reserve(4);

    Vector2 normalHeightB(rectB->getHalfHeight() * -sB, rectB->getHalfHeight() * cB);
    Vector2 normalWidthB(rectB->getHalfWidth() * cB, rectB->getHalfWidth() * sB);
    Vector2 centerB = b->getPosition();

    verticesB.emplace_back(centerB + normalHeightB + normalWidthB);
    verticesB.emplace_back(centerB - normalHeightB + normalWidthB);
    verticesB.emplace_back(centerB + normalHeightB - normalWidthB);
    verticesB.emplace_back(centerB - normalHeightB - normalWidthB);

    normalHeightA.normalize(); 
    normalWidthA.normalize(); 
    normalHeightB.normalize(); 
    normalWidthB.normalize();

    std::vector<Vector2> normals{ normalHeightA, normalWidthA, normalHeightB, normalWidthB};

    float minOverlap = std::numeric_limits<float>::infinity();
    Vector2 collisionNormal;

    for (const Vector2& axis : normals) {
        float minA = 0, maxA = 0;
        ProjectVertices(verticesA, axis, minA, maxA);
        float minB = 0, maxB = 0;
        ProjectVertices(verticesB, axis, minB, maxB);

        if (maxA < minB || maxB < minA) return CollisionManifold();
        else {
            float overlap = std::min(maxA, maxB) - std::max(minA, minB);
            if (overlap < minOverlap) {
                minOverlap = overlap;
                collisionNormal = axis;
            }
        }
    }

    if ((centerA - centerB).dotProduct(collisionNormal) < 0)
        collisionNormal *= -1;

    return CollisionManifold(collisionNormal, minOverlap);
}

static void ProjectVertices(const std::vector<Vector2>& vertices, const Vector2& axis, float& min, float& max) {
    if (vertices.empty()) return;

    min = max = vertices[0].dotProduct(axis);
    float temp = 0;

    for (int i = 1; i < vertices.size(); i++) {
        temp = vertices[i].dotProduct(axis);

        if (temp > max) max = temp;
        else if (temp < min) min = temp;
    }
}