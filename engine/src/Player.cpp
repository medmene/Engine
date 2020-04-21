#include "include/Player.h"
#include "include/GameObject.h"
#include "include/KeyboardInput.h"

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

void Player::Init(SDL_Renderer * renderer, const string & resName, ResourceManager::Type type)
{
	m_renderer = renderer;
	m_playerObject = new GameObject(m_renderer, resName, type);
}

void Player::Update(float dt)
{
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
			m_speed.x = -m_speedConst.x;
			break;
		case KeyboardInput::D:
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
