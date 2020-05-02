#pragma once
#include "Core.h"
#include "Vector2.h"

class ICharacter;
class PathFinder;

class MovingController
{
	MovingController();
public:
	explicit MovingController(ICharacter * owner, const Vector2 & speedMod);
	~MovingController();
	
	void MoveToPos(const Vector2 &pos);
	bool IsMoving() { return m_moving; }

	void Update(float dt);
private:
	Vector2							m_speedModifier;
	Vector2							m_curSpeed;
	PathFinder					  * m_finder = nullptr;
	map<string, int>				m_directionsOfAnimations;
	
	ICharacter					  * m_owner = nullptr;
	bool							m_moving;
};