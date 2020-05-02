#include "include/MovingController.h"
#include "include/PathFinder.h"
#include "include/Character.h"

MovingController::MovingController()
	: m_speedModifier(0.16f, 0.12f)
	, m_curSpeed(Vector2::zero)
	, m_moving(false)
{
}

MovingController::MovingController(ICharacter * owner, const Vector2 & speedMod)
	: m_speedModifier(speedMod)
	, m_curSpeed(Vector2::zero)
	, m_moving(false)
	, m_owner(owner)
{
	m_directionsOfAnimations["_left"] = 0;
	m_directionsOfAnimations["_top_left"] = 1;
	m_directionsOfAnimations["_top"] = 2;
	m_directionsOfAnimations["_top_right"] = 3;
	m_directionsOfAnimations["_right"] = 4;
	m_directionsOfAnimations["_bottom_right"] = 5;
	m_directionsOfAnimations["_bottom"] = 6;
	m_directionsOfAnimations["_bottom_left"] = 7;

	m_finder = new PathFinder();
}

MovingController::~MovingController()
{
	if (m_finder)
	{
		delete m_finder;
	}
}

void MovingController::MoveToPos(const Vector2 &pos)
{
	// if (m_finder && m_owner)
	// {
	// 	m_finder->StartFinding()
	// }
}

void MovingController::Update(float dt)
{
	
}
