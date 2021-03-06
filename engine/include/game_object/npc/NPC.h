#pragma once
#include "include/game_object/npc/Character.h"
#include "include/game_object/GameObject.h"

class GameObject;
class PassabilityArea;
class BehaviourController;
class TextBubble;

class NPC: public GameObject, public ICharacter
{
public:
	NPC(const string & name);
	virtual ~NPC();
	void LoadGraphics(pugi::xml_node * node) override;

	void UpdatePos(const Vector2 & pos) override;
	TextBubble * GetTextObject() override { return m_bubble; }
	PassabilityArea * GetPassabilityArea() override { return m_passabilityArea; }
	shared_ptr<BehaviourController> GetBehviourController() { return m_behaviourController; }
	
	void Update(float dt) override;
	void Render() override;
private:
	string								m_npcName;
	PassabilityArea					  * m_passabilityArea = nullptr;
	bool								m_drawPassability = false;
	TextBubble						  * m_bubble = nullptr;
	
	shared_ptr<BehaviourController>		m_behaviourController;
	void ManageDebugInfo();
};