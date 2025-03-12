#pragma once

class Vector2D {
public: 
	float x, y;

	Vector2D();
	Vector2D(float x, float y);
	Vector2D(Vector2D const& vector2D);
	~Vector2D();

	Vector2D operator+(Vector2D const& vector2D) const;
	Vector2D operator-(Vector2D const& vector2D) const;
	Vector2D operator*(float const& number) const;
	Vector2D operator*(Vector2D const& vector2D) const;
	Vector2D operator/(float const& number) const;
	Vector2D operator/(Vector2D const& vector2D) const;

	Vector2D operator=(Vector2D const& vector2D);
	bool operator==(Vector2D const& vector2D) const;
	bool operator!=(Vector2D const& vector2D) const;

	Vector2D operator-() const;

	float Magnitude() const;
	Vector2D Normalize();
	Vector2D Normalized() const;
	float Distance(Vector2D const& vector2D) const;
	float Distance(Vector2D const& Vector2D_POINT_A, Vector2D const& Vector2D_POINT_B) const;
	float Dot(Vector2D const& vector2D) const;
	float Dot(Vector2D const& Vector2D_A, Vector2D const& Vector2D_B) const;
	float Angle() const;
	float Angle(Vector2D const& vector2D) const;
	Vector2D Rotate(float angle) const;
};