#pragma once


enum class ShapeType {
	Circle,
	Box
};

class Shape {
protected:
	ShapeType type;
public:
	Shape(ShapeType t) : type(t) {}
	virtual ~Shape() = default;

	ShapeType getType() const {
		return type;
	}
};