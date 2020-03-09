//#include "include/BoundingBox3.h"
//
//
//
//BoundingBox3::BoundingBox3()
//	: min(-1,-1,-1)
//	, max(1,1,1)
//{
//}
//
//BoundingBox3::BoundingBox3(const Vector3 &min_, const Vector3 &max_)
//	: min(min_)
//	, max(max_)
//{
//}
//
//BoundingBox3::BoundingBox3(const BoundingBox3& other)
//	: min(other.min)
//	, max(other.max)
//{
//}
//
//
//BoundingBox3::~BoundingBox3()
//{
//}
//
//void BoundingBox3::SetMin(const Vector3 &min_)
//{
//	min = min_;
//}
//
//void BoundingBox3::SetMax(const Vector3 &max_)
//{
//	max = max_;
//}
//
//Vector3 BoundingBox3::GetMin() const
//{
//	return min;
//}
//
//Vector3 BoundingBox3::GetMax() const
//{
//	return max;
//}
//
//void BoundingBox3::scale(float scale)
//{
//	if (scale > 0)
//	{
//		min.scale(scale);
//		max.scale(scale);
//	}
//}
//
//Vector3 BoundingBox3::size() const
//{
//	return max - min;
//}
//
//Vector3 BoundingBox3::position() const
//{
//	return (max + min) / 2;
//}
//
//BoundingBox3& BoundingBox3::operator=(const BoundingBox3& other)
//{
//	if (this == &other)
//	{
//		return *this;
//	}
//	min = other.min;
//	max = other.max;
//	return *this;
//}
//
//bool BoundingBox3::operator==(const BoundingBox3& other) const
//{
//	return min == other.min && max == other.max;
//}
//
//bool BoundingBox3::operator!=(const BoundingBox3& other) const
//{
//	return min != other.min || max != other.max;
//}
