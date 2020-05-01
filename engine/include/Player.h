#pragma once
#include "Core.h"
#include "Vector2.h"

class GameObject;
class PassabilityArea;

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

	PassabilityArea				  * m_passabilityArea = nullptr;
	bool							m_drawPassability = false;

// ----------------------------------------------------- //
	bool							m_jumping = false;
	float							m_timer = 0.f;
	float							m_currDistance = 0.f;
	float							m_jumpDuration = 0.f;
	bool							m_oldGravity = false;
	float							m_jumpHeight = 40.f;
	
	void Jump(float duration);
};