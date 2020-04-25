#include "include/Vector2.h"

Vector2::Vector2()
	: x(0)
	, y(0)
{
}

Vector2::Vector2(const Vector2& other)
	: x(other.x)
	, y(other.y)
{	
}

Vector2::Vector2(int xPos, int yPos)
	: x(static_cast<float>(xPos))
	, y(static_cast<float>(yPos))
{	
}

Vector2::Vector2(int xPos, float yPos)
	: x(static_cast<float>(xPos))
	, y(yPos)
{
}

Vector2::Vector2(float xPos, float yPos)
	: x(xPos)
	, y(yPos)
{
}

Vector2::Vector2(float xPos, int yPos)
	: x(xPos)
	, y(static_cast<float>(yPos))
{
}

void Vector2::scale(float scale)
{
	this->x *= scale;
	this->y *= scale;
}

Vector2 & Vector2::operator=(const Vector2 & other)
{
	x = other.x;
	y = other.y;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	return this->x == other.x && this->y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return this->x != other.x || this->y != other.y;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
	return  *this;
}

Vector2& Vector2::operator+=(int other)
{
	this->x += other;
	this->y += other;
	return  *this;
}

Vector2& Vector2::operator+=(float other)
{
	this->x += other;
	this->y += other;
	return  *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return  *this;
}

Vector2& Vector2::operator-=(int other)
{
	this->x -= other;
	this->y -= other;
	return  *this;
}

Vector2& Vector2::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
	return  *this;
}

Vector2& Vector2::operator/=(int other)
{
	this->x /= other;
	this->y /= other;
	return  *this;
}

Vector2& Vector2::operator/=(float other)
{
	this->x /= other;
	this->y /= other;
	return  *this;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 operator*(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}
