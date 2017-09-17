#include "vector.h"

namespace MagusEngine
{
	Vector2f::Vector2f()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2f::Vector2f(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2f Vector2f::operator+(const Vector2f& b) {
		return Vector2f(x + b.x, y + b.y);
	}	
	Vector2f Vector2f::operator-(const Vector2f& b) {
		return Vector2f(x - b.x, y - b.y);
	}	
	Vector2f Vector2f::operator*(const Vector2f& b) {
		return Vector2f(x * b.x, y * b.y);
	}
	Vector2f Vector2f::operator/(const Vector2f& b){
		return Vector2f(x / b.x, y / b.y);
	}

	Vector2f Vector2f::operator+(const float& b) {
		return Vector2f(x + b, y + b);
	}
	Vector2f Vector2f::operator-(const float& b) {
		return Vector2f(x - b, y - b);
	}
	Vector2f Vector2f::operator*(const float& b) {
		return Vector2f(x * b, y * b);
	}
	Vector2f Vector2f::operator/(const float& b) {
		return Vector2f(x / b, y / b);
	}

	float Vector2f::Length()
	{
		return (float)sqrt((x * x) + (y * y));
	}

	void Vector2f::Normalise()
	{
		float length = Length();

		x = x / length;
		y = y / length;
	}


	float Vector2f::Cross(Vector2f* other)
	{
		return (x * other->y) - (y * other->x);
	}

	Vector3f::Vector3f()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3f::Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3f Vector3f::operator+(const Vector3f& b) {
		return Vector3f(x + b.x, y + b.y, z + b.z);
	}
	Vector3f Vector3f::operator-(const Vector3f& b) {
		return Vector3f(x - b.x, y - b.y, z - b.z);
	}
	Vector3f Vector3f::operator*(const Vector3f& b) {
		return Vector3f(x * b.x, y * b.y, z * b.z);
	}
	Vector3f Vector3f::operator/(const Vector3f& b) {
		return Vector3f(x / b.x, y / b.y, z / b.z);
	}

	Vector3f Vector3f::operator+(const float& b) {
		return Vector3f(x + b, y + b, z + b);
	}
	Vector3f Vector3f::operator-(const float& b) {
		return Vector3f(x - b, y - b, z - b);
	}
	Vector3f Vector3f::operator*(const float& b) {
		return Vector3f(x * b, y * b, z * b);
	}
	Vector3f Vector3f::operator/(const float& b) {
		return Vector3f(x / b, y / b, z / b);
	}

	Vector4f::Vector4f()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	Vector4f::Vector4f(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}


	Vector4f Vector4f::Lerp(Vector4f dest, float factor)
	{
		return dest - (*this) * factor + (*this);
	}

	Vector4f Vector4f::operator+(const Vector4f& b) {
		return Vector4f(x + b.x, y + b.y, z + b.z, w + b.w);
	}
	Vector4f Vector4f::operator-(const Vector4f& b) {
		return Vector4f(x - b.x, y - b.y, z - b.z, w - b.w);
	}
	Vector4f Vector4f::operator*(const Vector4f& b) {
		return Vector4f(x * b.x, y * b.y, z * b.z, w * b.w);
	}
	Vector4f Vector4f::operator/(const Vector4f& b) {
		return Vector4f(x / b.x, y / b.y, z / b.z, w / b.w);
	}

	Vector4f Vector4f::operator+(const float& b) {
		return Vector4f(x + b, y + b, z + b, w + b);
	}
	Vector4f Vector4f::operator-(const float& b) {
		return Vector4f(x - b, y - b, z - b, w - b);
	}
	Vector4f Vector4f::operator*(const float& b) {
		return Vector4f(x * b, y * b, z * b, w * b);
	}
	Vector4f Vector4f::operator/(const float& b) {
		return Vector4f(x / b, y / b, z / b, w / b);
	}

}