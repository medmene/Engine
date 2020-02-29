#pragma once

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(const Vector3 & other);
	
	Vector3(int xPos, int yPos, int zPos);
	Vector3(int xPos, int yPos, float zPos);
	Vector3(int xPos, float yPos, float zPos);
	Vector3(int xPos, float yPos, int zPos);
	Vector3(float xPos, int yPos, int zPos);
	Vector3(float xPos, int yPos, float zPos);
	Vector3(float xPos, float yPos, int zPos);
	Vector3(float xPos, float yPos, float zPos);

	void scale(float scale);

	Vector3& operator=(const Vector3& other);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(int other);
	Vector3& operator+=(float other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(int other);
	Vector3& operator-=(float other);
	Vector3& operator/(int other);
	Vector3& operator/(float other);
};