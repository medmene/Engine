#include "include/NPC.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/PassabilityMap.h"
#include "include/Camera.h"
#include "include/KeyboardInput.h"
#include "include/BehaviourController.h"
#include "include/TextBubble.h"


NPC::NPC(const string & src)
	: GameObject(src)
	, m_npcName("npc")
{
}

NPC::~NPC()
{
	delete m_bubble;
	delete m_passabilityArea;
	delete m_behaviourController;
}

void NPC::Init()
{
	m_bubble = new TextBubble("textBubble_settings.gobj");
	m_bubble->SetParent(this);
	m_bubble->SetVisible(false);
	m_bubble->SetSide(TextBubble::LEFT);

	m_behaviourController = new BehaviourController(m_renderer, this);

	m_passabilityArea = new PassabilityArea(GetCenterPos(), GetSize().x * 0.25f,
		Vector2(0, m_passOffsetCoef * GetSize().y));
}

void NPC::Update(float dt)
{
	if (!IsVisible())
	{
		return;
	}
	
	m_passabilityArea->UpdatePos(GetCenterPos());
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
			Vector2 localPos = m_passabilityArea->m_pos;

			localPos.x *= Camera::instance()->GetZoom();
			localPos.y *= Camera::instance()->GetZoom();

			auto diff = Camera::instance()->GetDiff();
			localPos.x = localPos.x + diff.x;
			localPos.y = localPos.y + diff.y;

			SDL_DrawCircle(m_renderer, localPos, m_passabilityArea->m_radius* Camera::instance()->GetZoom());
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
