#include "sVector3.h"

sVector3::sVector3()
	: x(0)
	, y(0)
	, z(0)
{
}

sVector3::sVector3(const sVector3& other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
{
}

sVector3::sVector3(int xPos, int yPos, int zPos)
	: x(static_cast<float>(xPos))
	, y(static_cast<float>(yPos))
	, z(static_cast<float>(zPos))
{
}

sVector3::sVector3(int xPos, int yPos, float zPos)
	: x(static_cast<float>(xPos))
	, y(static_cast<float>(yPos))
	, z(zPos)
{
}

sVector3::sVector3(int xPos, float yPos, float zPos)
	: x(static_cast<float>(xPos))
	, y(yPos)
	, z(zPos)
{
}

sVector3::sVector3(int xPos, float yPos, int zPos)
	: x(static_cast<float>(xPos))
	, y(yPos)
	, z(static_cast<float>(zPos))
{
}

sVector3::sVector3(float xPos, int yPos, int zPos)
	: x(xPos)
	, y(static_cast<float>(yPos))
	, z(static_cast<float>(zPos))
{
}

sVector3::sVector3(float xPos, int yPos, float zPos)
	: x(xPos)
	, y(static_cast<float>(yPos))
	, z(zPos)
{
}

sVector3::sVector3(float xPos, float yPos, int zPos)
	: x(xPos)
	, y(yPos)
	, z(static_cast<float>(zPos))
{
}

sVector3::sVector3(float xPos, float yPos, float zPos)
	: x(xPos)
	, y(yPos)
	, z(zPos)
{
}

float sVector3::get_x() const
{
	return this->x;
}

int sVector3::get_x_int() const
{
	return static_cast<int>(this->x);
}

float sVector3::get_y() const
{
	return this->y;
}

int sVector3::get_y_int() const
{
	return static_cast<int>(this->y);
}

float sVector3::get_z() const
{
	return this->z;
}

int sVector3::get_z_int() const
{
	return static_cast<int>(this->z);
}

void sVector3::set_x(float xPos)
{
	this->x = xPos;
}

void sVector3::set_y(float yPos)
{
	this->y = yPos;
}

void sVector3::set_z(float zPos)
{
	this->z = zPos;
}

void sVector3::scale(float scale)
{
	if (scale > 0)
	{
		this->x *= scale;
		this->y *= scale;
		this->z *= scale;
	}
}

sVector3& sVector3::operator=(const sVector3& other)
{
	if (this == &other)
	{
		return *this;
	}
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

bool sVector3::operator==(const sVector3& other) const
{
	return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool sVector3::operator!=(const sVector3& other) const
{
	return this->x != other.x || this->y != other.y || this->z != other.z;
}

sVector3& sVector3::operator+=(const sVector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return  *this;
}

sVector3& sVector3::operator+=(int other)
{
	this->x += other;
	this->y += other;
	this->z += other;
	return  *this;
}

sVector3& sVector3::operator+=(float other)
{
	this->x += other;
	this->y += other;
	this->z += other;
	return  *this;
}

sVector3& sVector3::operator-=(const sVector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return  *this;
}

sVector3& sVector3::operator-=(int other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
	return  *this;
}

sVector3& sVector3::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
	return  *this;
}

sVector3& sVector3::operator/(int other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
	return  *this;
}

sVector3& sVector3::operator/(float other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
	return  *this;
}

sVector3 operator+(const sVector3& lhs, const sVector3& rhs)
{
	return sVector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

sVector3 operator-(const sVector3& lhs, const sVector3& rhs)
{
	return sVector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
