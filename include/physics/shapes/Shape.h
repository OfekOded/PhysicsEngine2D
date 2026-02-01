#pragma once
#include "physics/math/Vector2.h"

enum class ShapeType {
	Circle,
	Box
};

struct AABB {
	Vector2 min;
	Vector2 max;
};


class Shape {
protected:
	ShapeType type;
public:
	Shape(ShapeType t) : type(t) {}
	virtual ~Shape() = default;
	virtual AABB getAABB(const Vector2& position, float rotation) const = 0;

	ShapeType getType() const {
		return type;
	}
};