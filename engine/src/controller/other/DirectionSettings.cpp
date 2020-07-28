#include "include/controller/other/DirectionSettings.h"




map<int, string> DirectionSettings::m_directionsOfAnimations;
int DirectionSettings::m_dirs[3][3];

void DirectionSettings::CollectAnimations()
{
	m_directionsOfAnimations[0] = "_left";
	m_directionsOfAnimations[1] = "_top_left";
	m_directionsOfAnimations[2] = "_top";
	m_directionsOfAnimations[3] = "_top_right";
	m_directionsOfAnimations[4] = "_right";
	m_directionsOfAnimations[5] = "_bottom_right";
	m_directionsOfAnimations[6] = "_bottom";
	m_directionsOfAnimations[7] = "_bottom_left";

	m_dirs[0][0] = 1;
	m_dirs[0][1] = 0;
	m_dirs[0][2] = 7;
	m_dirs[1][0] = 2;
	m_dirs[1][2] = 6;
	m_dirs[2][0] = 3;
	m_dirs[2][1] = 4;
	m_dirs[2][2] = 5;
}

string DirectionSettings::GetDirectionAnimation(MovingState state, int direction)
{
	string anim;
	switch (state)
	{
	case RUNNING:
		anim += "running";
		break;
	case GOING:
		anim += "going";
		break;
	case IDLE:
		anim += "idle";
		break;
	}
	return anim + m_directionsOfAnimations[direction];
}

int DirectionSettings::VelocityToDirection(const Vector2& velocity)
{
	int signX = (velocity.x > 0) - (velocity.x < 0) + 1; // 0 1 2
	int signY = (velocity.y > 0) - (velocity.y < 0) + 1; // 0 1 2

	return m_dirs[signX][signY];
}