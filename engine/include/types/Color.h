#pragma once

class Color
{
public:
	Color();
	Color(const Color & other);
	Color(int _r, int _g, int _b, int _a);

	void SetR(int _r) { r = _r; fixupColor(); }
	void SetG(int _g) { g = _g; fixupColor(); }
	void SetB(int _b) { b = _b; fixupColor(); }
	void SetA(int _a) { a = _a; fixupColor(); }

	int GetR() { return r; }
	int GetG() { return g; }
	int GetB() { return b; }
	int GetA() { return a; }

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
	int r;
	int g;
	int b;
	int a;

	void fixupColor();
};