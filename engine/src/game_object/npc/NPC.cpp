#include "include/game_object/npc/NPC.h"
#include "include/game_object/GameObject.h"
#include "include/controller/Animator.h"
#include "include/controller/PassabilityMap.h"
#include "include/input/Camera.h"
#include "include/input/KeyboardInput.h"
#include "include/controller/BehaviourController.h"
#include "include/game_object/TextBubble.h"
#include "pugixml/pugixml.hpp"




NPC::NPC(const string & name)
	: GameObject(name)
	, m_npcName("npc")
{
}

void NPC::LoadGraphics(pugi::xml_node * node)
{
	GameObject::LoadGraphics(node);

	SetAnimationEnable(true);
	GetAnimator()->GetActiveAnimation()->Play();

	m_bubble = new TextBubble("npc_textBubble");
	m_bubble->LoadGraphics(&node->child("text_bubble"));
	m_bubble->SetParent(this);
	m_bubble->SetVisible(false);
	m_bubble->SetSide(TextBubble::LEFT);

	m_passabilityArea = new PassabilityArea(GetCenterPos(), GetSize().x * 0.1f);
	m_behaviourController = make_shared<BehaviourController>(m_renderer, this);
}

NPC::~NPC()
{
	delete m_bubble;
	delete m_passabilityArea;
}

void NPC::UpdatePos(const Vector2& pos)
{
	GameObject::UpdatePos(pos);
	if (m_passabilityArea)
	{
		m_passabilityArea->UpdatePos(GetPivotPos());
	}
}

void NPC::Update(float dt)
{
	if (!IsVisible())
	{
		return;
	}
	ManageDebugInfo();
	
	m_passabilityArea->UpdatePos(GetPivotPos());
	m_behaviourController->Update(dt);
	m_bubble->Update(dt);
	GameObject::Update(dt);
}

void NPC::Render()
{
	if (IsVisible())
	{
		m_behaviourController->Render();
		m_bubble->Render();
		GameObject::Render();

		if (m_drawPassability)
		{
			Vector2 localPos = m_passabilityArea->GetPos();

			localPos.x *= Camera::instance()->GetZoom();
			localPos.y *= Camera::instance()->GetZoom();

			auto diff = Camera::instance()->GetDiff();
			localPos.x = localPos.x + diff.x;
			localPos.y = localPos.y + diff.y;

			SDL_DrawCircle(m_renderer, localPos, m_passabilityArea->GetRadius() * Camera::instance()->GetZoom());
		}
	}
}

void NPC::ManageDebugInfo()
{
	if (KeyboardInput::instance()->GetState() == kb::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == kb::I)
		{
			m_drawPassability = !m_drawPassability;
		}
	}
}
