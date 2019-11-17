#include "sBoundingBox.h"



sBoundingBox::sBoundingBox()
	: min(-1,-1,-1)
	, max(1,1,1)
{
}

sBoundingBox::sBoundingBox(const sVector3 &min_, const sVector3 &max_)
	: min(min_)
	, max(max_)
{
}

sBoundingBox::sBoundingBox(const sBoundingBox& other)
	: min(other.min)
	, max(other.max)
{
}


sBoundingBox::~sBoundingBox()
{
}

void sBoundingBox::SetMin(const sVector3 &min_)
{
	min = min_;
}

void sBoundingBox::SetMax(const sVector3 &max_)
{
	max = max_;
}

sVector3 sBoundingBox::GetMin() const
{
	return min;
}

sVector3 sBoundingBox::GetMax() const
{
	return max;
}

void sBoundingBox::scale(float scale)
{
	if (scale > 0)
	{
		min.scale(scale);
		max.scale(scale);
	}
}

sVector3 sBoundingBox::size() const
{
	return max - min;
}

sVector3 sBoundingBox::position() const
{
	return (max + min) / 2;
}

sBoundingBox& sBoundingBox::operator=(const sBoundingBox& other)
{
	if (this == &other)
	{
		return *this;
	}
	min = other.min;
	max = other.max;
	return *this;
}

bool sBoundingBox::operator==(const sBoundingBox& other) const
{
	return min == other.min && max == other.max;
}

bool sBoundingBox::operator!=(const sBoundingBox& other) const
{
	return min != other.min || max != other.max;
}
