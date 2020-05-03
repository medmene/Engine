#include "include/Player.h"
#include "include/GameObject.h"
#include "include/KeyboardInput.h"
#include "include/ResourceManager.h"
#include "include/Animator.h"
#include "include/PassabilityMap.h"
#include "include/Camera.h"
#include "include/TextBubble.h"


Player::Player()
	: m_playerName("player")
	, m_speed(0, 0)
	, m_speedConst(0.16f, 0.12f)
	, m_noclip(false)
{
}

Player::~Player()
{
	if (m_playerObject) { delete m_playerObject; }
	if (m_passabilityArea) { delete m_passabilityArea; }
	if (m_bubble) { delete m_bubble; }
}

void Player::Init(SDL_Renderer * renderer)
{
	m_renderer = renderer;
	
	m_playerObject = new GameObject(m_renderer, "Player", ResourceManager::GOBJECT);
	m_playerObject->SetAnimationEnable(true);
	m_playerObject->GetAnimator()->GetActiveAnimation()->Play();
	m_playerObject->UpdatePos(Vector2(500, 1400));

	m_bubble = new TextBubble(renderer, "playerTextBubble_settings", ResourceManager::GOBJECT);
	m_bubble->SetParent(m_playerObject);
	m_bubble->SetSide(TextBubble::LEFT);
	
	Vector2 pos = m_playerObject->GetCenterPos();
	pos.y += m_passOffsetCoef * m_playerObject->GetSize().y;
	m_passabilityArea = new PassabilityArea(pos, m_playerObject->GetSize().x * 0.25f);
}

bool Player::IsVisible()
{
	return m_playerObject->IsVisible();
}

void Player::SetVisible(bool visible)
{
	m_playerObject->SetVisible(visible);
}

void Player::Update(float dt)
{
	if (!m_playerObject->IsVisible())
	{
		return;
	}
	
	if (KeyboardInput::instance()->GetState() == kb::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == kb::I)
		{
			m_drawPassability = !m_drawPassability;
		}
		if (KeyboardInput::instance()->GetKey() == kb::U)
		{
			m_noclip = !m_noclip;
		}
	}
	
	m_playerObject->Update(dt);
	m_bubble->Update(dt);

	m_speed.x = 0;
	m_speed.y = 0;
	
	if (KeyboardInput::instance()->GetKeyMap().empty()) 
	{
		m_speed.x = 0;
		m_speed.y = 0;
	}
	else 
	{
		auto key = KeyboardInput::instance()->GetKeyMap()[KeyboardInput::instance()->GetKeyMap().size() - 1];
		switch (key)
		{
		case kb::W:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("going_left"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("going_left");
			}
			m_speed.y = -m_speedConst.y;
			break;
		case kb::A:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("idle_left"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("idle_left");
			}
			m_speed.x = -m_speedConst.x;
			break;
		case kb::D:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("idle_right"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("idle_right");
			}
			m_speed.x = m_speedConst.x;
			break;
		case kb::S:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("going_right"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("going_right");
			}
			m_speed.y = m_speedConst.y;
			break;
		}

		if (!m_noclip)
		{
			if (m_speed != Vector2::zero)
			{
				Vector2 pos = m_playerObject->GetCenterPos();
				Vector2 oldPos = m_passabilityArea->m_pos;
				pos.y += m_passOffsetCoef * m_playerObject->GetSize().y;
				m_passabilityArea->m_pos = pos + m_speed;

				if (PassabilityMap::instance()->IsAreaPossible(m_passabilityArea))
				{
					auto oldPos = GetGameObject()->GetPosition();
					oldPos += m_speed;
					GetGameObject()->UpdatePos(oldPos);
				}
				else
				{
					m_passabilityArea->m_pos = oldPos;
				}
			}
		}
		else
		{
			Vector2 pos = m_playerObject->GetCenterPos();
			pos.y += m_passOffsetCoef * m_playerObject->GetSize().y;
			m_passabilityArea->m_pos = pos;
			
			auto oldPos = GetGameObject()->GetPosition();
			oldPos += Vector2(m_speed.x * 1.5f, m_speed.y * 1.5f);
			GetGameObject()->UpdatePos(oldPos);
		}
	}
}

void Player::Render()
{
	m_playerObject->Render();
	m_bubble->Render();

	if (m_drawPassability)
	{
		Vector2 localPos = m_passabilityArea->m_pos;
		
		auto diff = Camera::instance()->GetDiff();
		localPos.x = localPos.x + diff.x;
		localPos.y = localPos.y + diff.y;
		
		SDL_DrawCircle(m_renderer, localPos, m_passabilityArea->m_radius);
	}
}


//
// if (m_jumping)
// {
// 	m_timer += dt;
// 	auto oldPos = m_playerObject->GetPosition();
// 	float coef;
//
// 	if (m_timer <= m_jumpDuration / 2)
// 	{
// 		coef = m_timer / m_jumpDuration * 2;
// 	}
// 	else
// 	{
// 		coef = 1 - (m_timer - m_jumpDuration * .5f) / m_jumpDuration * 2;
// 	}
//
// 	oldPos.y -= m_currDistance;
// 	m_currDistance = coef * m_jumpHeight;
// 	oldPos.y += m_currDistance;
//
// 	m_playerObject->UpdatePos(oldPos);
//
// 	if (m_timer >= m_jumpDuration)
// 	{
// 		m_timer = 0.f;
// 		m_jumping = false;
// 		m_playerObject->SetGravity(m_oldGravity);
// 	}
// }
//
//
//
//
// void Player::Jump(float duration)
// {
// 	if (!m_jumping)
// 	{
// 		m_timer = 0.f;
// 		m_currDistance = 0.f;
// 		m_jumping = true;
// 		m_jumpDuration = duration;
// 		m_oldGravity = m_playerObject->IsGravityEnabled();
// 		m_playerObject->SetGravity(false);
// 	}
// }
