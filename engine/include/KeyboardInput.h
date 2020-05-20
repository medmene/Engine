#pragma once
#include "Core.h"
#include "Vector2.h"
#include "KeyboardBinds.h"

using namespace kb;

class KeyboardInput
{
	KeyboardInput();
public:
	static KeyboardInput * instance();

	State GetState() { return m_state; }
	Key GetKey() { return m_key; }
	
	vector<int> GetKeyModMap() const { return m_keyModMap; }
	vector<int> GetKeyMap() const { return m_keyMap; }
	bool IsKeyPressed(int key);
	bool IsModActive(int mod);

	void LockInput() { m_locked = true; }
	void UnlockInput() { m_locked = false; }
	bool IsLocked() { return m_locked; }
	
	void Reset();
	void Update(SDL_Event * e);
private:
	vector<int>					m_keyMap;
	vector<int>					m_keyModMap;
	State						m_state;
	Key							m_key;
	bool						m_locked;

	static KeyboardInput	  * sm_instance;
};