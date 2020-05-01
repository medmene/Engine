#pragma once
#include "Core.h"
#include "Vector2.h"

class GameObject;

class Player
{
public:
	Player();
	~Player();
	
	void Init(SDL_Renderer * renderer, const Vector2 & wSize);

	GameObject * GetGameObject() { return m_playerObject; }

	void Update(float dt);
	void Render();
private:
	SDL_Renderer				  * m_renderer = nullptr;
	GameObject					  * m_playerObject = nullptr;
	string							m_playerName;

	Vector2							m_speed;
	Vector2							m_speedConst;
	Vector2							m_winSize;
	//Vector2						m_acceleration;
};