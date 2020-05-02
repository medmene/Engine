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

	void SetVisualisation(bool visualisation) { m_visualisation = visualisation; }

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
	vector<Vector2>					m_movingPath;
	int								m_pathIndex;

	int								m_dirs[3][3];
	ICharacter					  * m_owner = nullptr;
	bool							m_visualisation;
};