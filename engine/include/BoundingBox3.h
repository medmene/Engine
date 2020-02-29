#pragma once
#include "Vector3.h"

class BoundingBox3
{
public:
	BoundingBox3();
	BoundingBox3(const Vector3 &min_, const Vector3 &max_);
	BoundingBox3(const BoundingBox3 & other);
	~BoundingBox3();

	void SetMin(const Vector3 &min_);
	void SetMax(const Vector3 &max_);
	Vector3 GetMin() const;
	Vector3 GetMax() const;
	void scale(float scale);
	Vector3 size() const;
	Vector3 position() const;

	BoundingBox3& operator=(const BoundingBox3& other);
	bool operator==(const BoundingBox3& other) const;
	bool operator!=(const BoundingBox3& other) const;

private:
	Vector3 min;
	Vector3 max;
};

