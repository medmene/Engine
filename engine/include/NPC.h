#pragma once
#include "Core.h"
#include "Character.h"
#include "ResourceManager.h"

class GameObject;
class PassabilityArea;
class BehaviourController;
class TextBubble;

class NPC: public ICharacter
{
public:
	NPC(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	virtual ~NPC();

	void Init();

	bool IsVisible() override;
	void SetVisible(bool visible)override;
	void SetPassabilityOffsetCoef(float offset) { m_passOffsetCoef = offset; }
	
	GameObject * GetGameObject() override { return m_npcObject; }
	TextBubble * GetTextObject() override { return m_bubble; }
	PassabilityArea * GetPassabilityArea() override { return m_passabilityArea; }
	
	void Update(float dt) override;
	void Render() override;
private:
	SDL_Renderer				  * m_renderer = nullptr;
	GameObject					  * m_npcObject = nullptr;
	string							m_npcName;
	
	PassabilityArea				  * m_passabilityArea = nullptr;
	bool							m_drawPassability = false;
	float							m_passOffsetCoef = 0.1f;

	TextBubble					  * m_bubble = nullptr;
	
	BehaviourController			  * m_behaviourController = nullptr;
};