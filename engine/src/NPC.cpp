#include "include/NPC.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/PassabilityMap.h"
#include "include/Camera.h"


NPC::NPC()
	: m_playerName("player")
	, m_speed(0, 0)
	, m_speedConst(0.16f, 0.12f)
{
}

NPC::~NPC()
{
	if (m_npcObject)
	{
		delete m_npcObject;
	}
}

void NPC::Init(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
{
	m_renderer = renderer;

	m_npcObject = new GameObject(m_renderer, src, type);
	m_npcObject->SetAnimationEnable(true);
	m_npcObject->GetAnimator()->GetActiveAnimation()->Play();
	m_npcObject->UpdatePos(Vector2(750, 1000));
	m_npcObject->UpdateColor(Color(50,250,50,255));
	m_npcObject->UpdateSize(Vector2(180, 180));

	Vector2 pos = m_npcObject->GetCenterPos();
	pos.y += m_npcObject->GetSize().y / 3;
	m_passabilityArea = new PassabilityArea(pos, m_npcObject->GetSize().x * 0.25f);
}

bool NPC::IsVisible()
{
	return m_npcObject->IsVisible();
}

void NPC::SetVisible(bool visible)
{
	m_npcObject->SetVisible(visible);
}

void NPC::Update(float dt)
{
	m_npcObject->Update(dt);
}

void NPC::Render()
{
	m_npcObject->Render();

	if (m_drawPassability)
	{
		Vector2 localPos = m_passabilityArea->m_pos;
		
		auto diff =Camera::instance()->GetDiff();
		
		localPos.x = localPos.x + diff.x;
		localPos.y = localPos.y + diff.y;

		SDL_DrawCircle(m_renderer, localPos, m_passabilityArea->m_radius);
	}
}
