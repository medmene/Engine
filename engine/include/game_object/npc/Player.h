#pragma once
#include "include/game_object/npc/Character.h"
#include "include/game_object/GameObject.h"

class PassabilityArea;
class TextBubble;

class Player : public GameObject, public ICharacter
{
public:
	Player(const string & name);
	virtual ~Player();
	void LoadGraphics(pugi::xml_node * node) override;

	void UpdatePos(const Vector2 & pos) override;
	TextBubble * GetTextObject() override { return m_bubble; }
	PassabilityArea * GetPassabilityArea() override { return m_passabilityArea; }

	void Update(float dt) override;
	void Render() override;
	
private:
	string							m_playerName;
	Vector2							m_velocity;
	Vector2							m_velocityConst;
	PassabilityArea				  * m_passabilityArea = nullptr;
	bool							m_drawPassability = false;
	TextBubble					  * m_bubble = nullptr;
	bool							m_noclip;
	int								m_lastDirection;
	bool							m_running;
	
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