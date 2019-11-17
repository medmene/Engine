#include "sVector2.h"

sVector2::sVector2()
	: x(0)
	, y(0)
{
}

sVector2::sVector2(const sVector2& other)
	: x(other.x)
	, y(other.y)
{	
}

sVector2::sVector2(int xPos, int yPos)
	: x(static_cast<float>(xPos))
	, y(static_cast<float>(yPos))
{	
}

sVector2::sVector2(int xPos, float yPos)
	: x(static_cast<float>(xPos))
	, y(yPos)
{
}

sVector2::sVector2(float xPos, float yPos)
	: x(xPos)
	, y(yPos)
{
}

sVector2::sVector2(float xPos, int yPos)
	: x(xPos)
	, y(static_cast<float>(yPos))
{
}

float sVector2::get_x() const
{
	return this->x;
}

int sVector2::get_x_int() const
{
	return static_cast<int>(this->x);
}

float sVector2::get_y() const
{
	return this->y;
}

int sVector2::get_y_int() const
{
	return static_cast<int>(this->y);
}

void sVector2::set_x(float xPos)
{
	this->x = xPos;
}

void sVector2::set_y(float yPos)
{
	this->y = yPos;
}

void sVector2::scale(float scale)
{
	if (scale > 0)
	{
		this->x *= scale;
		this->y *= scale;
	}
}

sVector2& sVector2::operator=(const sVector2& other)
{
	if (this == &other)
	{
		return *this;
	}
	x = other.x;
	y = other.y;
	return *this;
}

bool sVector2::operator==(const sVector2& other) const
{
	return this->x == other.x && this->y == other.y;
}

bool sVector2::operator!=(const sVector2& other) const
{
	return this->x != other.x || this->y != other.y;
}

sVector2& sVector2::operator+=(const sVector2& other)
{
	this->x += other.x;
	this->y += other.y;
	return  *this;
}

sVector2& sVector2::operator+=(int other)
{
	this->x += other;
	this->y += other;
	return  *this;
}

sVector2& sVector2::operator+=(float other)
{
	this->x += other;
	this->y += other;
	return  *this;
}

sVector2& sVector2::operator-=(const sVector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return  *this;
}

sVector2& sVector2::operator-=(int other)
{
	this->x -= other;
	this->y -= other;
	return  *this;
}

sVector2& sVector2::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
	return  *this;
}

sVector2& sVector2::operator/(int other)
{
	this->x /= other;
	this->y /= other;
	return  *this;
}

sVector2& sVector2::operator/(float other)
{
	this->x /= other;
	this->y /= other;
	return  *this;
}

sVector2 operator+(const sVector2& lhs, const sVector2& rhs)
{
	return sVector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

sVector2 operator-(const sVector2& lhs, const sVector2& rhs)
{
	return sVector2(lhs.x - rhs.x, lhs.y - rhs.y);
}
