#pragma once
#include "Core.h"
#include "Vector2.h"


class MouseInput
{
	MouseInput();
public:
	enum Button
	{
		MOUSE_LEFT = 0,
		MOUSE_MIDDLE,
		MOUSE_RIGHT,
		MOUSE_4,
		MOUSE_5,
		MOUSE_UNDEFINED = 5
	};
	enum State
	{
		MOUSE_BUTTON_DOWN = 0,
		MOUSE_BUTTON_UP,
		MOUSE_BUTTON_UNDEFINED
	};

	static MouseInput * instance();

	bool IsPressed(Button btn) { return m_pressed[btn]; }
	Vector2 GetPos() const { return m_pos; }
	Vector2 GetPosInMap();
	Vector2 GetDiff() const { return m_diff; }
	int GetWheel() { return m_wheel; }

	Button GetButton() const { return m_button; }
	State GetState() const { return m_state; }
	int GetClicks() { return m_clicks; }

	void LockInput() { m_locked = true; }
	void UnlockInput() { m_locked = false; }
	bool IsLocked() { return m_locked; }
	
	void ResetDiffs();

	void Update(SDL_Event * e);
private:
	Button					m_button;
	State					m_state;
	int						m_clicks;
	Vector2					m_pos;
	Vector2					m_diff;
	bool					m_pressed[6];
	int						m_wheel;
	bool					m_locked;

	static MouseInput	  * sm_instance;
};