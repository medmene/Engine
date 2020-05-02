#pragma once
#include "Core.h"
#include "Vector2.h"


class KeyboardInput
{
public:
	enum State
	{
		KEY_DOWN = 0,
		KEY_UP,
		KEY_UNDEFINED
	};
	
	enum Key
	{
		W = 119,
		A = 97,
		D = 100,
		S = 115,
		SPACE = 32,
		L = 108,
		O = 111,
		P = 112,
		I = 105
	};
	
	enum Mod
	{
		CTRL = 224,
		RCTRL = 228,
		ALT = 226,
		RALT = 230,
		SHIFT = 225,
		RSHIFT = 229
	};
	
	KeyboardInput(){}
	~KeyboardInput(){}
	static KeyboardInput * instance() { return sm_instance; }

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