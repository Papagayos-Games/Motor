#include "Vector3.h"

#include <iostream>
#include <math.h>

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) 
{
}

Vector3::Vector3(const float x1, const float y1, const float z1) :
	x(x1), y(y1), z(z1)
{
}

void Vector3::invert()
{
	x = -x;
	y = -y;
	z = -z;
}

float Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::squareMagnitude() const
{
	return x * x + y * y + z * z;
}

void Vector3::operator*=(const float k)
{
	x *= k;
	y *= k;
	z = k;
}

Vector3 Vector3::operator*(const float k)
{
	return Vector3(x*k, y*k, z*k);
}


float Vector3::normalize()
{
	float m = magnitude();
	*this *= 1.0f / m;
	return m;
}

float Vector3::operator*(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

float Vector3::dot(const Vector3& v) const
{
	return x*v.x + y*v.y + z* v.z;
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

void Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

void Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

bool Vector3::operator==(const Vector3& other)
{
	return x == other.x && y == other.y && z == other.z;
}

Vector3 Vector3::operator%(const Vector3& v)
{
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

void Vector3::set(Vector3 v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::setX(float n)
{
	x = n;
}

void Vector3::setY(float n)
{
	y = n;
}

void Vector3::setZ(float n)
{
	z = n;
}