#include "include/BehaviourController.h"
#include "include/MovingController.h"
#include "include/GameObject.h"
#include "include/PassabilityMap.h"
#include "include/KeyboardInput.h"
#include "include/Camera.h"
#include "include/TextBubble.h"
#include "include/DirectionSettings.h"






BehaviourController::BehaviourController(SDL_Renderer* r, ICharacter* owner)
	: m_renderer(r)
	, m_owner(owner)
	, m_anchorArea(Vector2(20, 20))
	, m_freeBehaviour(true)
	, m_running(false)
	, m_normalSpeed(0.07f)
	, m_runSpeed(0.15f)
{
	m_ownerObj = dynamic_cast<GameObject *>(owner);
	
	m_movingController = make_shared<MovingController>(this, r, owner, m_normalSpeed);
	m_currentState = UNDEFINED;
	m_anchorPoint = m_ownerObj->GetCenterPos();
	
	ChangeState(WAIT);
}

void BehaviourController::SetupDefaultSettings()
{
	SetAnchorPoint(m_ownerObj->GetCenterPos());
	SetAnchorArea(Vector2(8, 8));
}

void BehaviourController::Update(float dt)
{
	if (KeyboardInput::instance()->GetState() == kb::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == kb::I)
		{
			m_visualisation = !m_visualisation;
		}
	}

	if (m_freeBehaviour)
	{
		// State 1.
		if (m_currentState == WAIT)
		{
			if (m_waitingTime > 0.f)
			{
				m_waitingTime -= dt;
				if (m_waitingTime <= 0.f)
				{
					m_waitingTime = 0.f;
					ChangeState(MOVE);
				}
			}
		}

		// State 2.
		if (m_currentState == MOVE)
		{
			if (!m_movingController->IsMoving())
			{
				if (!m_movingController->CanMove())
				{
					ChangeState(MOVE, true);
				}
				else
				{
					ChangeState(TALK);
				}
			}
		}

		// State 3.
		if (m_currentState == TALK)
		{
			if (m_waitingTime > 0.f)
			{
				m_waitingTime -= dt;
				if (m_waitingTime <= 0.f)
				{
					m_waitingTime = 0.f;
					m_owner->GetTextObject()->SetVisible(false);
					ChangeState(WAIT);
				}
			}
		}
	}
	
	m_movingController->Update(dt);
}


void BehaviourController::ChangeState(BehaviourState newState, bool force)
{
	if (m_currentState != newState || force)
	{
		m_currentState = newState;

		switch (m_currentState)
		{
		case MOVE:
			OnStateMoveEntering();
			break;
		case WAIT:
			OnStateWaitEntering();
			break;
		case TALK:
			OnStateTalkEntering();
			break;
		case BATTLE:
			OnStateBattleEntering();
			break;
		}
	}
}

void BehaviourController::OnStateWaitEntering()
{
	m_waitingTime = 1000.f + rand() % 3000;
}

void BehaviourController::OnStateMoveEntering()
{
	auto pos = m_anchorPoint;
	pos = PassabilityMap::instance()->WorldToNodeIndex(pos);
	pos.x += rand() % (int)m_anchorArea.x - m_anchorArea.x / 2;
	pos.y += rand() % (int)m_anchorArea.y - m_anchorArea.y / 2;

	pos = PassabilityMap::instance()->NodeIndexToWorld(pos);
	m_movingController->MoveToPos(Vector2(pos));
}

void BehaviourController::OnStateTalkEntering()
{
	m_waitingTime = 2000.f + rand() % 2000;
	if (m_owner->GetTextObject())
	{
		m_owner->GetTextObject()->SetVisible(true);
		m_owner->GetTextObject()->SetText(u"������ ��� ���� ������� �������");
	}
}

void BehaviourController::OnStateBattleEntering()
{
}

void BehaviourController::Render()
{
	m_movingController->Render();

	if (m_visualisation)
	{
		auto diff = Camera::instance()->GetDiff();

		SDL_SetRenderDrawColor(m_renderer, 0, 150, 150, 100);
		SDL_Rect rct = { (int)m_anchorPoint.x - 7, (int)m_anchorPoint.y - 7 , 15, 15 };

		rct.x *= Camera::instance()->GetZoom();
		rct.y *= Camera::instance()->GetZoom();
		rct.w *= Camera::instance()->GetZoom();
		rct.h *= Camera::instance()->GetZoom();
		rct.x = rct.x + diff.x;
		rct.y = rct.y + diff.y;
		
		SDL_RenderFillRect(m_renderer, &rct);

		auto pos = m_anchorPoint;
		pos.x -= m_anchorArea.x / 2 * PassabilityMap::instance()->GetNodeSize().x;
		pos.y -= m_anchorArea.y / 2 * PassabilityMap::instance()->GetNodeSize().y;

		auto end = m_anchorPoint;
		end.x += m_anchorArea.x / 2 * PassabilityMap::instance()->GetNodeSize().x;
		end.y += m_anchorArea.y / 2 * PassabilityMap::instance()->GetNodeSize().y;

		auto size = end - pos;

		SDL_SetRenderDrawColor(m_renderer, 0, 150, 150, 100);
		rct = { (int)pos.x, (int)pos.y, (int)size.x, (int)size.y };
		
		rct.x *= Camera::instance()->GetZoom();
		rct.y *= Camera::instance()->GetZoom();
		rct.w *= Camera::instance()->GetZoom();
		rct.h *= Camera::instance()->GetZoom();
		rct.x = rct.x + diff.x;
		rct.y = rct.y + diff.y;
		
		SDL_RenderFillRect(m_renderer, &rct);
	}
}
