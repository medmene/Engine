#pragma once
#include "Core.h"
#include "Vector2.h"

class ICharacter;
class PathFinder;
class GameObject;
class BehaviourController;

class MovingController
{
	MovingController();
public:
	explicit MovingController(BehaviourController *ctrl, SDL_Renderer *r, ICharacter * owner, float speedMod);
	~MovingController();
	
	void MoveToPos(const Vector2 &pos);
	bool IsMoving() { return m_moving || m_searching; }
	bool CanMove() { return m_hasPath; }

	void SetSpeed(float speed) { m_speedModifier = speed; }
	void SetVisualisation(bool visualisation) { m_visualisation = visualisation; }

	float GetNormalSpeed() { return m_speedModifier; }
	int GetLastDir() { return m_lastDir; }
	
	void Update(float dt);
	void Render();
private:
	SDL_Renderer				  * m_renderer = nullptr;
	float							m_speedModifier;
	Vector2							m_curSpeed;
	
	PathFinder					  * m_finder = nullptr;
	bool							m_searching;
	bool							m_moving;
	bool							m_hasPath;
	vector<Vector2>					m_movingPath;
	int								m_pathIndex;

	int								m_lastDir;
	ICharacter					  * m_owner = nullptr;
	GameObject					  * m_ownerObj = nullptr;
	bool							m_visualisation;
	BehaviourController			  * m_behaviour;
};