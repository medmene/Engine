#pragma once
#include "Core.h"
#include "GameObject.h"
#include "Character.h"

class GameObject;
class PassabilityArea;
class BehaviourController;
class TextBubble;

class NPC: public GameObject, public ICharacter
{
public:
	NPC(SDL_Renderer * renderer, const string & src);
	virtual ~NPC();

	void Init();

	void SetPassabilityOffsetCoef(float offset) { m_passOffsetCoef = offset; }
	
	TextBubble * GetTextObject() { return m_bubble; }
	PassabilityArea * GetPassabilityArea() { return m_passabilityArea; }
	
	void Update(float dt) override;
	void Render() override;
private:
	string							m_npcName;
	PassabilityArea				  * m_passabilityArea = nullptr;
	bool							m_drawPassability = false;
	float							m_passOffsetCoef = 0.1f;
	TextBubble					  * m_bubble = nullptr;
	
	BehaviourController			  * m_behaviourController = nullptr;
	void ManageDebugInfo();
};