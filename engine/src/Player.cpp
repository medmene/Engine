#include "include/Player.h"
#include "include/GameObject.h"
#include "include/KeyboardInput.h"
#include "include/ResourceManager.h"
#include "include/Animator.h"


Player::Player()
	: m_playerName("player")
	, m_speed(0, 0)
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
	m_playerObject->GetAnimator()->GetActiveAnimation()->Play();
	m_playerObject->UpdatePos(Vector2(m_winSize.x / 2 - m_playerObject->GetSize().x / 2
		, 320 - m_playerObject->GetSize().y / 2));
}

void Player::Update(float dt)
{
	m_playerObject->Update(dt);
	
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
			m_speed.y = -m_speedConst.y;
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
			m_speed.y = m_speedConst.y;
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
