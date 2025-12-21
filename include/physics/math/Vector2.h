#pragma once
#include <cmath>

class Vector2 {
public:
	float x;
	float y;

	Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

	Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator*(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(float scalar) const {
		return Vector2(x / scalar, y / scalar);
	}

	Vector2& operator+=(const Vector2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2& operator*=(const Vector2& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	float dotProduct(const Vector2& v) const {
		return x * v.x + y * v.y;
	}

	float lengthSquared() const {
		return x * x + y * y;
	}

	float length() const {
		return std::sqrt(lengthSquared());
	}

	void normalize() {
		float len = length();
		if (len > 0) {
			x /= len;
			y /= len;
		}
	}

	float distance(const Vector2& v) const {
		return (*this - v).length();
	}

	float distanceSquared(const Vector2& v) const {
		return (*this - v).lengthSquared();
	}

	Vector2 perpendicular() const {
		return Vector2(-y, x);
	}
};