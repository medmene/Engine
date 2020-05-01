#include "include/Physics.h"
#include  <cmath>


Impulse::Impulse()
	: m_acceleration(Vector2::zero)
	, m_time(0)
	, m_currDiff(Vector2::zero)
{
}

Impulse::Impulse(const Vector2& accel, float time)
	: m_acceleration(accel)
	, m_time(time)
	, m_currDiff(Vector2::zero)
{
}

Vector2 & Impulse::ApplyImpulse(const Vector2& influencing, float dt)
{
	m_time -= dt;

	m_currDiff += m_acceleration + influencing;
	
	if (m_time < 0.f)
	{
		m_time = 0;
	}
	return m_currDiff;
}


// OLD IMPULSE

// Impulse::Impulse()
// 	: m_speed(Vector2::zero)
// 	, m_acceleration(0.f)
// {
// }
//
// Impulse::Impulse(const Vector2 & speed, float acceleration)
// 	: m_speed(speed)
// 	, m_acceleration(acceleration)
// {
// }
//
// void Impulse::ApplyImpulse()
// {
// 	float oldX = m_speed.x;
// 	float oldY = m_speed.y;
//
// 	float xSpeed = 0.f, ySpeed = 0.f;
// 	if (oldX != 0 && oldY != 0)
// 	{
// 		float coefX = oldX / oldY;
// 		float coefY = oldY / oldX;
// 		xSpeed = sqrt(m_acceleration * m_acceleration / (coefX * coefX + 1));
// 		ySpeed = sqrt(m_acceleration * m_acceleration / (coefY * coefY + 1));
// 	}
// 	else if (oldX != 0)
// 	{
// 		xSpeed = m_acceleration;
// 	}
// 	else if (oldY != 0)
// 	{
// 		ySpeed = m_acceleration;
// 	}
//
// 	auto checkX = [this, &oldX]()
// 	{
// 		if ((m_speed.x > 0 && oldX < 0) || (m_speed.x < 0 && oldX > 0))
// 		{
// 			m_speed.x = 0.f;
// 		}
// 	};
//
// 	auto checkY = [this, &oldY]()
// 	{
// 		if ((m_speed.y > 0 && oldY < 0) || (m_speed.y < 0 && oldY > 0))
// 		{
// 			m_speed.y = 0.f;
// 		}
// 	};
// 	
// 	if (m_speed.x > 0)
// 	{
// 		m_speed.x -= xSpeed;
// 		checkX();
// 	}
// 	else if (m_speed.x < 0)
// 	{
// 		m_speed.x += xSpeed;
// 		checkX();
// 	}
//
// 	if (m_speed.y > 0)
// 	{
// 		m_speed.y -= ySpeed;
// 		checkY();
// 	}
// 	else if (m_speed.y < 0)
// 	{
// 		m_speed.y += ySpeed;
// 		checkY();
// 	}
// }
