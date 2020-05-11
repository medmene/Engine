#include "include/Player.h"
#include "include/GameObject.h"
#include "include/KeyboardInput.h"
#include "include/Animator.h"
#include "include/PassabilityMap.h"
#include "include/Camera.h"
#include "include/TextBubble.h"


Player::Player(const string & src)
	: GameObject(src)
	, m_playerName("player")
	, m_velocity(0, 0)
	, m_velocityConst(0.16f, 0.12f)
	, m_noclip(false)
{
	SetAnimationEnable(true);
	GetAnimator()->GetActiveAnimation()->Play();
	Player::UpdatePos(Vector2(500, 500));
	
	m_bubble = new TextBubble("playerTextBubble_settings.gobj");
	m_bubble->SetParent(this);
	m_bubble->SetVisible(false);
	m_bubble->SetSide(TextBubble::LEFT);

	m_passabilityArea = new PassabilityArea (GetCenterPos(), GetSize().x * 0.25f, 
		Vector2(0,m_passOffsetCoef * GetSize().y));
}

Player::~Player()
{
	delete m_passabilityArea;
	delete m_bubble;
}

void Player::UpdatePos(const Vector2& pos)
{
	GameObject::UpdatePos(pos);
	if (m_passabilityArea)
	{
		m_passabilityArea->UpdatePos(GetCenterPos());
	}
}

void Player::Update(float dt)
{
	if (!IsVisible())
	{
		return;
	}
	
	ManageDebugInfo();
	
	GameObject::Update(dt);
	m_bubble->Update(dt);

	m_velocity.x = 0;
	m_velocity.y = 0;
	
	if (KeyboardInput::instance()->GetKeyMap().empty()) 
	{
		m_velocity.x = 0;
		m_velocity.y = 0;
	}
	else 
	{
		UpdateVelocity();
		
		if (m_velocity != Vector2::zero)
		{
			if (m_noclip)
			{
				m_passabilityArea->UpdatePos(GetCenterPos());
				UpdatePos(GetPosition() + m_velocity * 2.f);
			}
			else
			{
				auto oldArea = *m_passabilityArea;
				m_passabilityArea->UpdatePos(GetCenterPos() + m_velocity);

				if (PassabilityMap::instance()->IsAreaPossible(m_passabilityArea))
				{
					UpdateCenterPos(GetCenterPos() + m_velocity);
				}
				else
				{
					*m_passabilityArea = oldArea;
				}
			}
		}
	}
}

void Player::Render()
{
	if (IsVisible())
	{
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
			
			SDL_DrawCircle(m_renderer, localPos, m_passabilityArea->m_radius * Camera::instance()->GetZoom());
		}
	}
}

void Player::UpdateVelocity()
{
	auto key = KeyboardInput::instance()->GetKeyMap()[KeyboardInput::instance()->GetKeyMap().size() - 1];
	switch (key)
	{
	case kb::W:
		if (!GetAnimator()->IsAnimationPlaying("going_top"))
		{
			GetAnimator()->PlayAnimation("going_top");
		}
		m_velocity.y = -m_velocityConst.y;
		break;
	case kb::A:
		if (!GetAnimator()->IsAnimationPlaying("going_left"))
		{
			GetAnimator()->PlayAnimation("going_left");
		}
		m_velocity.x = -m_velocityConst.x;
		break;
	case kb::D:
		if (!GetAnimator()->IsAnimationPlaying("going_right"))
		{
			GetAnimator()->PlayAnimation("going_right");
		}
		m_velocity.x = m_velocityConst.x;
		break;
	case kb::S:
		if (!GetAnimator()->IsAnimationPlaying("going_bottom"))
		{
			GetAnimator()->PlayAnimation("going_bottom");
		}
		m_velocity.y = m_velocityConst.y;
		break;
	}
}

void Player::ManageDebugInfo()
{
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
