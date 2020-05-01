#pragma once
#include "include/Vector2.h"




struct Impulse
{
	Vector2			m_acceleration;
	float			m_time;
	Vector2			m_currDiff;
	
	explicit Impulse();
	explicit Impulse(const Vector2& accel, float time);

	Vector2 & ApplyImpulse(const Vector2& influencing, float dt);
	
	Impulse& operator=(const Impulse& other) = default;
};


 // OLD IMPUSLE
 // it's fun

// struct Impulse
// {
// 	Vector2		m_speed;
// 	float		m_acceleration;
// 	
// 	Impulse();
// 	Impulse(const Vector2 & speed, float acceleration);
//
// 	void ApplyImpulse();
//
// 	Impulse& operator=(const Impulse& other) = default;
// };