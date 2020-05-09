#pragma once
#include "Core.h"
#include "Vector2.h"
#include "GameObject.h"

class PassabilityArea;
class TextBubble;

class Player : public GameObject
{
public:
	Player(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	virtual ~Player();

	void SetPassabilityOffsetCoef(float offset) { m_passOffsetCoef = offset; }
	
	TextBubble * GetTextObject() { return m_bubble; }
	PassabilityArea * GetPassabilityArea() { return m_passabilityArea; }

	void Update(float dt) override;
	void Render() override;
	
private:
	string							m_playerName;
	Vector2							m_velocity;
	Vector2							m_velocityConst;
	PassabilityArea				  * m_passabilityArea = nullptr;
	bool							m_drawPassability = false;
	float							m_passOffsetCoef = 0.33f;
	TextBubble					  * m_bubble;
	bool							m_noclip;

	void UpdateVelocity();
	void ManageDebugInfo();
};


/*// ----------------------------------------------------- //
	bool							m_jumping = false;
	float							m_timer = 0.f;
	float							m_currDistance = 0.f;
	float							m_jumpDuration = 0.f;
	bool							m_oldGravity = false;
	float							m_jumpHeight = 40.f;
	
	void Jump(float duration);*/