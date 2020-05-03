#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Character.h"

class GameObject;
class PassabilityArea;

class Player : public ICharacter
{
public:
	Player();
	virtual ~Player();
	void Init(SDL_Renderer * renderer);

	bool IsVisible() override;
	void SetVisible(bool visible) override;
	void SetPassabilityOffsetCoef(float offset) { m_passOffsetCoef = offset; }
	GameObject * GetGameObject() override { return m_playerObject; }

	void Update(float dt) override;
	void Render() override;
	
private:
	SDL_Renderer				  * m_renderer = nullptr;
	GameObject					  * m_playerObject = nullptr;
	string							m_playerName;

	Vector2							m_speed;
	Vector2							m_speedConst;

	PassabilityArea				  * m_passabilityArea = nullptr;
	bool							m_drawPassability = false;
	float							m_passOffsetCoef = 0.33f;

	bool							m_noclip;
};


/*// ----------------------------------------------------- //
	bool							m_jumping = false;
	float							m_timer = 0.f;
	float							m_currDistance = 0.f;
	float							m_jumpDuration = 0.f;
	bool							m_oldGravity = false;
	float							m_jumpHeight = 40.f;
	
	void Jump(float duration);*/