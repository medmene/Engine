#include "include/Vector3.h"

Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0)
{
}

Vector3::Vector3(const Vector3& other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
{
}

Vector3::Vector3(int xPos, int yPos, int zPos)
	: x(static_cast<float>(xPos))
	, y(static_cast<float>(yPos))
	, z(static_cast<float>(zPos))
{
}

Vector3::Vector3(int xPos, int yPos, float zPos)
	: x(static_cast<float>(xPos))
	, y(static_cast<float>(yPos))
	, z(zPos)
{
}

Vector3::Vector3(int xPos, float yPos, float zPos)
	: x(static_cast<float>(xPos))
	, y(yPos)
	, z(zPos)
{
}

Vector3::Vector3(int xPos, float yPos, int zPos)
	: x(static_cast<float>(xPos))
	, y(yPos)
	, z(static_cast<float>(zPos))
{
}

Vector3::Vector3(float xPos, int yPos, int zPos)
	: x(xPos)
	, y(static_cast<float>(yPos))
	, z(static_cast<float>(zPos))
{
}

Vector3::Vector3(float xPos, int yPos, float zPos)
	: x(xPos)
	, y(static_cast<float>(yPos))
	, z(zPos)
{
}

Vector3::Vector3(float xPos, float yPos, int zPos)
	: x(xPos)
	, y(yPos)
	, z(static_cast<float>(zPos))
{
}

Vector3::Vector3(float xPos, float yPos, float zPos)
	: x(xPos)
	, y(yPos)
	, z(zPos)
{
}

void Vector3::scale(float scale)
{
	this->x *= scale;
	this->y *= scale;
	this->z *= scale;
}

Vector3 & Vector3::operator=(const Vector3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return this->x != other.x || this->y != other.y || this->z != other.z;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return  *this;
}

Vector3& Vector3::operator+=(int other)
{
	this->x += other;
	this->y += other;
	this->z += other;
	return  *this;
}

Vector3& Vector3::operator+=(float other)
{
	this->x += other;
	this->y += other;
	this->z += other;
	return  *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return  *this;
}

Vector3& Vector3::operator-=(int other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
	return  *this;
}

Vector3& Vector3::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
	return  *this;
}

Vector3& Vector3::operator/(int other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
	return  *this;
}

Vector3& Vector3::operator/(float other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
	return  *this;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
