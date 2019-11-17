#pragma once

class sVector3
{
public:
	sVector3();
	sVector3(const sVector3 & other);
	
	sVector3(int xPos, int yPos, int zPos);	
	sVector3(int xPos, int yPos, float zPos);
	sVector3(int xPos, float yPos, float zPos);	
	sVector3(int xPos, float yPos, int zPos);
	sVector3(float xPos, int yPos, int zPos);	
	sVector3(float xPos, int yPos, float zPos);	
	sVector3(float xPos, float yPos, int zPos);	
	sVector3(float xPos, float yPos, float zPos);

	float get_x() const;
	int get_x_int() const;
	float get_y() const;
	int get_y_int() const;
	float get_z() const;
	int get_z_int() const;
	void set_x(float xPos);
	void set_y(float yPos);
	void set_z(float zPos);
	void scale(float scale);

	sVector3& operator=(const sVector3& other);
	bool operator==(const sVector3& other) const;
	bool operator!=(const sVector3& other) const;
	friend sVector3 operator+(const sVector3& lhs, const sVector3& rhs);
	friend sVector3 operator-(const sVector3& lhs, const sVector3& rhs);
	sVector3& operator+=(const sVector3& other);
	sVector3& operator+=(int other);
	sVector3& operator+=(float other);
	sVector3& operator-=(const sVector3& other);
	sVector3& operator-=(int other);
	sVector3& operator-=(float other);
	sVector3& operator/(int other);
	sVector3& operator/(float other);
private:
	float x;
	float y;
	float z;
};