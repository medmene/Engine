#pragma once
#include "Core.h"
#include "Vector2.h"


class KeyboardInput
{
public:
	enum Key
	{
		W = 119,
		A = 97,
		D = 100,
		S = 115,
		SPACE = 32
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

	const vector<int> & GetKeyModMap() { return m_keyModMap; }
	const vector<int> & GetKeyMap() { return m_keyMap; }
	bool IsKeyPressed(int key);
	bool IsModActive(int mod);

	void Update(SDL_Event * e);
private:
	vector<int>					m_keyMap;
	vector<int>					m_keyModMap;

	static KeyboardInput	  * sm_instance;
};