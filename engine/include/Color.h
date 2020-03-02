#pragma once

class Color
{
public:
	int r;
	int g;
	int b;
	int a;

	Color();
	Color(const Color & other);
	Color(int _r, int _g, int _b, int _a);

	Color& operator=(const Color& other);
	bool operator==(const Color& other) const;
	bool operator!=(const Color& other) const;
	Color& operator+=(const Color& other);
	Color& operator+=(int other);
	Color& operator+=(float other);
	Color& operator-=(const Color& other);
	Color& operator-=(int other);
	Color& operator-=(float other);
	Color& operator/=(int other);
	Color& operator/=(float other);
private:
	void fixupColor();
};