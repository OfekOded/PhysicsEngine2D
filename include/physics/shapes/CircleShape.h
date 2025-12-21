#pragma once
#include "Shape.h"

class CircleShape : public Shape {
private:
	float radius;
public:
	CircleShape(float r) : Shape(ShapeType::Circle), radius(r) {}

	float getRadius() const { return radius; }
	void setRadius(float r) { radius = r; }
};