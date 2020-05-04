#pragma once
#include "Core.h"
#include "Vector2.h"

class ICharacter;
class PathFinder;

class MovingController
{
	MovingController();
public:
	explicit MovingController(SDL_Renderer *r, ICharacter * owner, float speedMod);
	~MovingController();
	
	void MoveToPos(const Vector2 &pos);
	bool IsMoving() { return m_moving || m_searching; }
	bool CanMove() { return m_hasPath; }

	void SetSpeed(float speed) { m_speedModifier = speed; }
	void SetVisualisation(bool visualisation) { m_visualisation = visualisation; }
	void SetAnimationMap(map<int, string> mp) { m_directionsOfAnimations = mp; }

	float GetNormalSpeed() { return m_speedModifier; }
	float GetLastDir() { return m_lastDir; }
	auto GetAnimationMap() { return m_directionsOfAnimations; }
	
	void Update(float dt);
	void Render();
private:
	SDL_Renderer				  * m_renderer;
	float							m_speedModifier;
	Vector2							m_curSpeed;
	map<int, string>				m_directionsOfAnimations;
	
	PathFinder					  * m_finder = nullptr;
	bool							m_searching;
	bool							m_moving;
	bool							m_hasPath = false;
	vector<Vector2>					m_movingPath;
	int								m_pathIndex;

	int								m_dirs[3][3];
	int								m_lastDir;
	ICharacter					  * m_owner = nullptr;
	bool							m_visualisation;
};