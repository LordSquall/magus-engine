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

	float Vector3f::Length()
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	void Vector3f::Normalise()
	{
		float length = Length();

		x = x / length;
		y = y / length;
		z = z / length;
	}


	Vector3f Vector3f::Normalise(Vector3f v)
	{
		float length = v.Length();

		return Vector3f(v.x / length, v.y / length, v.z / length);
	}


	Vector3f Vector3f::Cross(Vector3f a, Vector3f b)
	{
		return Vector3f(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
	}

	Vector3f Vector3f::Cross(Vector3f* other)
	{
		Vector3f t;
		t.x = y * other->z - z * other->y;
		t.y = z * other->x - x * other->z;
		t.z = x * other->y - y * other->x;
		return t;
	}

	float Vector3f::Dot(Vector3f* other)
	{
		return x * other->x + y * other->y + z * other->z;
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