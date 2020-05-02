#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Character.h"
#include "ResourceManager.h"

class GameObject;
class PassabilityArea;

class NPC: public ICharacter
{
public:
	NPC();
	virtual ~NPC();

	void Init(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);

	bool IsVisible() override;
	void SetVisible(bool visible)override;
	
	void Update(float dt) override;
	void Render() override;
private:
	SDL_Renderer				  * m_renderer = nullptr;
	GameObject					  * m_npcObject = nullptr;
	string							m_playerName;

	Vector2							m_speed;
	Vector2							m_speedConst;

	PassabilityArea				  * m_passabilityArea = nullptr;
	bool							m_drawPassability = false;
};