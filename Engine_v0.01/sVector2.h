#pragma once

class sVector2
{
public:
	sVector2();
	sVector2(const sVector2 & other);
	sVector2(int xPos, int yPos);
	sVector2(int xPos, float yPos);
	sVector2(float xPos, float yPos);
	sVector2(float xPos, int yPos);

	float get_x() const;
	int get_x_int() const;
	float get_y() const;
	int get_y_int() const;
	void set_x(float xPos);
	void set_y(float yPos);
	void scale(float scale);
	
	sVector2& operator=(const sVector2& other);
	bool operator==(const sVector2& other) const;
	bool operator!=(const sVector2& other) const;
	friend sVector2 operator+(const sVector2& lhs, const sVector2& rhs);
	friend sVector2 operator-(const sVector2& lhs, const sVector2& rhs);
	sVector2& operator+=(const sVector2& other);
	sVector2& operator+=(int other);
	sVector2& operator+=(float other);
	sVector2& operator-=(const sVector2& other);
	sVector2& operator-=(int other);
	sVector2& operator-=(float other);
	sVector2& operator/(int other);
	sVector2& operator/(float other);
private:
	float x;
	float y;
};
