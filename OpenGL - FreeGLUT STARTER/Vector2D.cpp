#include "Vector2D.h"
#include <cmath>
#include "math.h"

Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
}
Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}
Vector2D::Vector2D(Vector2D const& vector2D) {
	this->x = vector2D.x;
	this->y = vector2D.y;
}

Vector2D::~Vector2D() {
}

/// <summary>
/// This function adds two vectors together.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
Vector2D Vector2D::operator+(Vector2D const& vector2D) const {
	return Vector2D(
		this->x + vector2D.x,
		this->y + vector2D.y
	);
}

/// <summary>
/// This function subtracts two vectors.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
Vector2D Vector2D::operator-(Vector2D const& vector2D) const {
	return Vector2D(
		this->x - vector2D.x,
		this->y - vector2D.y
	);
}

/// <summary>
///	This function multiplies a vector by a number.
/// </summary>
/// <param name="number"></param>
/// <returns></returns>
Vector2D Vector2D::operator*(float const& number) const {
	return Vector2D(
		this->x * number,
		this->y * number
	);
}

/// <summary>
///	This function multiplies two vectors together.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
Vector2D Vector2D::operator*(Vector2D const& vector2D) const {
	return Vector2D(
		this->x * vector2D.x,
		this->y * vector2D.y
	);
}

/// <summary>
/// This function divides a vector by a number.
/// </summary>
/// <param name="number"></param>
/// <returns></returns>
Vector2D Vector2D::operator/(float const& number) const {
	return Vector2D(
		this->x / number,
		this->y / number
	);
}

/// <summary>
/// This function divides two vectors.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
Vector2D Vector2D::operator/(Vector2D const& vector2D) const {
	return Vector2D(
		this->x / vector2D.x,
		this->y / vector2D.y
	);
}

/// <summary>
/// This function adds a vector to another vector.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
Vector2D Vector2D::operator=(Vector2D const& vector2D) {
	this->x = vector2D.x;
	this->y = vector2D.y;
	return *this;
}

/// <summary>
/// This function checks if two vectors are equal.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
bool Vector2D::operator==(Vector2D const& vector2D) const {
	return this->x == vector2D.x && this->y == vector2D.y;
}

/// <summary>
/// This function checks if two vectors are not equal.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
bool Vector2D::operator!=(Vector2D const& vector2D) const {
	return this->x != vector2D.x && this->y != vector2D.y;
}

/// <summary>
///	This function makes the vector negative.
/// </summary>
/// <returns></returns>
Vector2D Vector2D::operator-() const {
	return Vector2D(
		-this->x,
		-this->y
	);
}

/// <summary>
/// This function calculates the magnitude of a vector.
/// </summary>
/// <returns></returns>
float Vector2D::Magnitude() const {
	return sqrt(
		pow(this->x, 2) + pow(this->y, 2)
	);
}

/// <summary>
/// This function normalizes a vector.
/// </summary>
/// <returns></returns>
Vector2D Vector2D::Normalize() {
	float magnitude = this->Magnitude();
	return Vector2D(
		this->x / magnitude,
		this->y / magnitude
	);
}

/// <summary>
///	This function normalizes a vector. 
/// Does not change the original vector.
/// </summary>
/// <returns></returns>
Vector2D Vector2D::Normalized() const {
	float magnitude = this->Magnitude();
	Vector2D Normalized_Vector2D = Vector2D(
		this->x / magnitude,
		this->y / magnitude
	);
	return Normalized_Vector2D;
}

/// <summary>
/// This function calculates the distance between two vectors.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
float Vector2D::Distance(Vector2D const& vector2D) const {
	float Difference_X = this->x - vector2D.x;
	float POWER_DX = static_cast<float>(pow(Difference_X, 2));
	float Difference_Y = this->y - vector2D.y;
	float POWER_DY = static_cast<float>(pow(Difference_Y, 2));
	return sqrt(POWER_DX + POWER_DY);
}

/// <summary>
/// This function calculates the distance between two points.
/// </summary>
/// <param name="Vector2D_POINT_A"></param>
/// <param name="Vector2D_POINT_B"></param>
/// <returns></returns>
float Vector2D::Distance(Vector2D const& Vector2D_POINT_A, Vector2D const& Vector2D_POINT_B) const {
	float Difference_X = Vector2D_POINT_A.x - Vector2D_POINT_B.x;
	float POWER_DX = static_cast<float>(pow(Difference_X, 2));
	float Difference_Y = Vector2D_POINT_A.y - Vector2D_POINT_B.y;
	float POWER_DY = static_cast<float>(pow(Difference_Y, 2));
	return sqrt(POWER_DX + POWER_DY);
}

/// <summary>
/// This function calculates the dot product.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
float Vector2D::Dot(Vector2D const& vector2D) const {
	return this->x * vector2D.x + this->y * vector2D.y;
}

/// <summary>
/// This function calculates the dot product.
/// </summary>
/// <param name="Vector2D_A"></param>
/// <param name="Vector2D_B"></param>
/// <returns></returns>
float Vector2D::Dot(Vector2D const& Vector2D_A, Vector2D const& Vector2D_B) const {
	return Vector2D_A.x * Vector2D_B.x + Vector2D_A.x * Vector2D_B.y;
}

/// <summary>
/// This function give the angle of a vector.
/// </summary>
/// <returns></returns>
float Vector2D::Angle() const {
	if (x == 0.0f && y == 0.0f) {
		return 0.0f;
	}
	return atan2(y, x);
}

/// <summary>
/// This function gives the angle between two vectors.
/// </summary>
/// <param name="vector2D"></param>
/// <returns></returns>
float Vector2D::Angle(Vector2D const& vector2D) const {
	float Magnitude_This = this->Magnitude();
	float Magnitude_That = vector2D.Magnitude();

	if (Magnitude_This == 0.0f || Magnitude_That == 0.0f) {
		return 0.0f;
	}

	float Dot_Vector2D = this->Dot(vector2D);
	float Cosine_DV2D = Dot_Vector2D / (Magnitude_This * Magnitude_That);

	Cosine_DV2D = CLAMP(Cosine_DV2D, -1.0f, 1.0f);

    // Existing code
    Cosine_DV2D = CLAMP(Cosine_DV2D, -1.0f, 1.0f);
	return acos(Cosine_DV2D);
}

/// <summary>
/// This function rotates a vector.
/// Does not change the original vector.
/// </summary>
/// <param name="Angle_Degree"></param>
/// <returns></returns>
Vector2D Vector2D::Rotate(float Angle_Degree) const {
	float Angle_Radian = Angle_Degree * (PI / 180.0f); // Convert to radians
	float Cos_AR = cos(Angle_Radian);
	float Sin_AR = sin(Angle_Radian);

	float X = (this->x * Cos_AR) - (this->y * Sin_AR);
	float Y = (this->x * Sin_AR) + (this->y * Cos_AR);

	return Vector2D(X, Y);
}
