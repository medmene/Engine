#include "include/KeyboardInput.h"



KeyboardInput * KeyboardInput::sm_instance = new KeyboardInput();

bool KeyboardInput::IsKeyPressed(int key)
{
	auto it = find(m_keyMap.begin(), m_keyMap.end(), key);
	return it == m_keyMap.end();
}

bool KeyboardInput::IsModActive(int mod)
{
	auto it = find(m_keyModMap.begin(), m_keyModMap.end(), mod);
	return it == m_keyModMap.end();
}

void KeyboardInput::Update(SDL_Event * e)
{
	switch (e->type)
	{
	case SDL_KEYDOWN:
	{
		if (!e->key.repeat)
		{
			if (e->key.keysym.mod == 4096 || e->key.keysym.sym < 10000)
			{
				m_keyMap.emplace_back(e->key.keysym.sym);
			}
			else 
			{
				m_keyModMap.emplace_back(e->key.keysym.scancode);
			}
		}
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
