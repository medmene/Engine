#pragma once
#include "sVector3.h"

class sBoundingBox
{
public:
	sBoundingBox();
	sBoundingBox(const sVector3 &min_, const sVector3 &max_);
	sBoundingBox(const sBoundingBox & other);
	~sBoundingBox();

	void SetMin(const sVector3 &min_);
	void SetMax(const sVector3 &max_);
	sVector3 GetMin() const;
	sVector3 GetMax() const;
	void scale(float scale);
	sVector3 size() const;
	sVector3 position() const;

	sBoundingBox& operator=(const sBoundingBox& other);
	bool operator==(const sBoundingBox& other) const;
	bool operator!=(const sBoundingBox& other) const;

private:
	sVector3 min;
	sVector3 max;
};

