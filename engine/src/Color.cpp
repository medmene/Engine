#include "include/Color.h"

Color::Color()
	: r(0)
	, g(0)
	, b(0)
	, a(0)
{
}

Color::Color(const Color & other)
	: r(other.r)
	, g(other.g)
	, b(other.b)
	, a(other.a)
{
}

Color::Color(int _r, int _g, int _b, int _a)
	: r(_r)
	, g(_g)
	, b(_b)
	, a(_a)
{
}

Color & Color::operator=(const Color & other)
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
	return *this;
}

bool Color::operator==(const Color & other) const
{
	return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool Color::operator!=(const Color & other) const
{
	return r != other.r || g != other.g || b != other.b || a != other.a;
}

Color & Color::operator+=(const Color & other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;
	fixupColor();
	return *this;
}

Color & Color::operator+=(int other)
{
	r += other;
	g += other;
	b += other;
	a += other;
	fixupColor();
	return *this;
}

Color & Color::operator+=(float other)
{
	r += other;
	g += other;
	b += other;
	a += other;
	fixupColor();
	return *this;
}

Color & Color::operator-=(const Color & other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;
	fixupColor();
	return *this;
}

Color & Color::operator-=(int other)
{
	r -= other;
	g -= other;
	b -= other;
	a -= other;
	fixupColor();
	return *this;
}

Color & Color::operator-=(float other)
{
	r -= other;
	g -= other;
	b -= other;
	a -= other;
	fixupColor();
	return *this;
}

Color & Color::operator/=(int other)
{
	r /= other;
	g /= other;
	b /= other;
	a /= other;
	fixupColor();
	return *this;
}

Color & Color::operator/=(float other)
{
	r /= other;
	g /= other;
	b /= other;
	a /= other;
	fixupColor();
	return *this;
}

void Color::fixupColor()
{
	r = r > 255 ? 255 : r; r = r < 0 ? 0 : r;
	g = g > 255 ? 255 : g; g = g < 0 ? 0 : g;
	b = b > 255 ? 255 : b; b = b < 0 ? 0 : b;
	a = a > 255 ? 255 : a; a = a < 0 ? 0 : a;
}
