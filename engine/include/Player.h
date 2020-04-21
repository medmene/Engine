#pragma once
#include "Core.h"
#include "Vector2.h"
#include "include/ResourceManager.h"

class GameObject;

class Player
{
public:
	Player();
	~Player();
	void Init(SDL_Renderer * renderer, const string & resName, ResourceManager::Type type);

	GameObject * GetGameObject() { return m_playerObject; }

	void Update(float dt);

private:
	SDL_Renderer				  * m_renderer;
	GameObject					  * m_playerObject;
	string							m_playerName;

	Vector2							m_speed;
	Vector2							m_speedConst;
	//Vector2						m_acceleration;
};