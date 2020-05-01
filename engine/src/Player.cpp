#include "include/Player.h"
#include "include/GameObject.h"
#include "include/KeyboardInput.h"
#include "include/ResourceManager.h"
#include "include/Animator.h"
#include "include/Physics.h"


Player::Player()
	: m_playerName("player")
	, m_speed(0, 0)
	, m_jumping(false)
	, m_speedConst(0.16f, 0.16f)
{
}

Player::~Player()
{
	if (m_playerObject)
	{
		delete m_playerObject;
	}
}

void Player::Init(SDL_Renderer * renderer, const Vector2 & wSize)
{
	m_renderer = renderer;
	m_winSize = wSize;
	
	m_playerObject = new GameObject(m_renderer, "Player", ResourceManager::GOBJECT);
	m_playerObject->SetAnimationEnable(true);
	m_playerObject->SetGravity(true);
	m_playerObject->GetAnimator()->GetActiveAnimation()->Play();
	m_playerObject->UpdatePos(Vector2(m_winSize.x / 2 - m_playerObject->GetSize().x / 2
		, 320 - m_playerObject->GetSize().y / 2));
}

void Player::Update(float dt)
{
	m_playerObject->Update(dt);

	if (m_jumping)
	{
		m_timer += dt;
		auto oldPos = m_playerObject->GetPosition();
		float coef;
		
		if (m_timer <= m_jumpDuration / 2)
		{
			coef = m_timer / m_jumpDuration * 2;
		}
		else
		{
			coef = 1 - (m_timer - m_jumpDuration * .5f) / m_jumpDuration * 2;
		}

		oldPos.y -= m_currDistance;
		m_currDistance = coef * m_jumpHeight;
		oldPos.y += m_currDistance;
		
		m_playerObject->UpdatePos(oldPos);
		
		if (m_timer >= m_jumpDuration)
		{
			m_timer = 0.f;
			m_jumping = false;
			m_playerObject->SetGravity(m_oldGravity);
		}
	}

	
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
		case KeyboardInput::W:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("going_left"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("going_left");
			}
			Jump(400);
			break;
		case KeyboardInput::A:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("idle_left"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("idle_left");
			}
			m_speed.x = -m_speedConst.x;
			break;
		case KeyboardInput::D:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("idle_right"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("idle_right");
			}
			m_speed.x = m_speedConst.x;
			break;
		case KeyboardInput::S:
			if (!m_playerObject->GetAnimator()->IsAnimationPlaying("going_right"))
			{
				m_playerObject->GetAnimator()->PlayAnimation("going_right");
			}
			break;
		}
		auto oldPos = GetGameObject()->GetPosition();
		oldPos += m_speed;
		GetGameObject()->UpdatePos(oldPos);
	}
}

void Player::Render()
{
	m_playerObject->Render();
}

void Player::Jump(float duration)
{
	if (!m_jumping)
	{
		m_timer = 0.f;
		m_currDistance = 0.f;
		m_jumping = true;
		m_jumpDuration = duration;
		m_oldGravity = m_playerObject->IsGravityEnabled();
		m_playerObject->SetGravity(false);
	}
}
