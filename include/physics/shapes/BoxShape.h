#pragma once
#include "Shape.h"

class BoxShape : public Shape {
private:
	float width, height;
public:
	BoxShape(float w, float h) : Shape(ShapeType::Box), width(w), height(h) {}

	float getWidth() const { return width; }
	float getHeight() const { return height; }

	void setWidth(float w) { width = w; }
	void setHeight(float h) { height = h; }
};