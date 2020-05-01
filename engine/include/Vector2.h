#pragma once

class Vector2
{
public:
	float x;
	float y;

	static Vector2 uno;
	static Vector2 zero;

	Vector2();
	Vector2(const Vector2 & other);
	Vector2(int xPos, int yPos);
	Vector2(int xPos, float yPos);
	Vector2(float xPos, float yPos);
	Vector2(float xPos, int yPos);

	void scale(float scale);

	float length(const Vector2 other);
	
	Vector2& operator=(const Vector2& other);
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator*(const Vector2& lhs, const Vector2& rhs);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator+=(int other);
	Vector2& operator+=(float other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator-=(int other);
	Vector2& operator-=(float other);
	Vector2& operator/=(int other);
	Vector2& operator/=(float other);
};
