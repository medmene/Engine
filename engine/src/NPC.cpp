#include "include/NPC.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/PassabilityMap.h"
#include "include/Camera.h"
#include "include/KeyboardInput.h"
#include "include/MovingController.h"
#include "include/MouseInput.h"


NPC::NPC()
	: m_npcName("npc")
{
}

NPC::~NPC()
{
	if (m_npcObject)
	{
		delete m_npcObject;
	}

	if (m_passabilityArea)
	{
		delete m_passabilityArea;
	}

	if (m_movingController)
	{
		delete m_movingController;
	}
}

bool NPC::IsVisible()
{
	return m_npcObject->IsVisible();
}

void NPC::SetVisible(bool visible)
{
	m_npcObject->SetVisible(visible);
}

void NPC::Init(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
{
	m_renderer = renderer;

	m_movingController = new MovingController(this, Vector2(0.16f, 0.12f));
	
	m_npcObject = new GameObject(m_renderer, src, type);
	m_npcObject->SetAnimationEnable(true);
	m_npcObject->GetAnimator()->GetActiveAnimation()->Play();
	m_npcObject->UpdatePos(Vector2(750, 1000));
	m_npcObject->UpdateColor(Color(50,250,50,255));
	m_npcObject->UpdateSize(Vector2(180, 180));
	
	Vector2 pos = m_npcObject->GetCenterPos();
	pos.y += m_passOffsetCoef * m_npcObject->GetSize().y;
	m_passabilityArea = new PassabilityArea(pos, m_npcObject->GetSize().x * 0.25f);
}

void NPC::Update(float dt)
{
	if (KeyboardInput::instance()->GetState() == KeyboardInput::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == KeyboardInput::P)
		{
			m_drawPassability = !m_drawPassability;
		}
	}

	if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_DOWN)
	{
		if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_RIGHT)
		{
			if (m_movingController && !m_movingController->IsMoving())
			{
				m_movingController->MoveToPos(MouseInput::instance()->GetPosInMap());
			}
		}
	}
	
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
