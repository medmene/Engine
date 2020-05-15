#pragma once
#include "base_defs.h"
#include "Vector2.h"



class DirectionSettings
{
	DirectionSettings() = default;
public:
	enum MovingState
	{
		RUNNING = 0,
		GOING,
		IDLE
	};
	static void CollectAnimations();
	static string GetDirectionAnimation(MovingState state, int direction);
	static int VelocityToDirection(const Vector2 & velocity);
private:
	static map<int, string>		m_directionsOfAnimations;
	static int					m_dirs[3][3];
};