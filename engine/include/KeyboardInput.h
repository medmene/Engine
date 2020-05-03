#pragma once
#include "Core.h"
#include "Vector2.h"
#include "KeyboardBinds.h"

using namespace kb;

class KeyboardInput
{
	KeyboardInput();
public:
	~KeyboardInput(){}
	static KeyboardInput * instance();

	State GetState() { return m_state; }
	Key GetKey() { return m_key; }
	
	const vector<int> & GetKeyModMap() { return m_keyModMap; }
	const vector<int> & GetKeyMap() { return m_keyMap; }
	bool IsKeyPressed(int key);
	bool IsModActive(int mod);

	void Reset()
	{
		m_state = KEY_UNDEFINED;
		m_key = (Key)-100;
	}
	
	void Update(SDL_Event * e);
private:
	vector<int>					m_keyMap;
	vector<int>					m_keyModMap;

	State						m_state;
	Key							m_key;

	static KeyboardInput	  * sm_instance;
};