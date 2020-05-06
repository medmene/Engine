#include "include/KeyboardInput.h"



KeyboardInput * KeyboardInput::sm_instance = nullptr;

KeyboardInput::KeyboardInput()
	: m_state(State::KEY_UNDEFINED)
	, m_key(Key(0))
	, m_locked(false)
{
}

KeyboardInput* KeyboardInput::instance()
{
	if (!sm_instance)
	{
		sm_instance = new KeyboardInput();
	}
	return sm_instance;
}

bool KeyboardInput::IsKeyPressed(int key)
{
	auto it = find(m_keyMap.begin(), m_keyMap.end(), key);
	return it != m_keyMap.end();
}

bool KeyboardInput::IsModActive(int mod)
{
	auto it = find(m_keyModMap.begin(), m_keyModMap.end(), mod);
	return it != m_keyModMap.end();
}

void KeyboardInput::Reset()
{
	m_state = KEY_UNDEFINED;
	m_key = (Key)-100;
}

void KeyboardInput::Update(SDL_Event * e)
{
	if (m_locked) { return; }
	
	switch (e->type)
	{
	case SDL_KEYDOWN:
	{
		if (!e->key.repeat)
		{
			// TODO may be fix up this ?
			if (e->key.keysym.mod == 4096 || e->key.keysym.sym < 10000)
			{
				m_keyMap.emplace_back(e->key.keysym.sym);
			}
			else 
			{
				m_keyModMap.emplace_back(e->key.keysym.scancode);
			}
		}
		m_state = KEY_DOWN;
		m_key = (Key)e->key.keysym.sym;
		break;
	}
	case SDL_KEYUP:
	{
		auto it = find(m_keyModMap.begin(), m_keyModMap.end(), e->key.keysym.scancode);
		if (it != m_keyModMap.end())
		{
			m_keyModMap.erase(it);
		}
		else 
		{
			auto it = find(m_keyMap.begin(), m_keyMap.end(), e->key.keysym.sym);
			if (it != m_keyMap.end())
			{
				m_keyMap.erase(it);
			}
		}
		m_state = KEY_UP;
		m_key = (Key)e->key.keysym.sym;
		break;
	}
	case SDL_TEXTEDITING:
	{
		break;
	}
	case SDL_TEXTINPUT:
	{
		break;
	}
	// System?
	case SDL_KEYMAPCHANGED:
	{
		break;
	}
	}
}
