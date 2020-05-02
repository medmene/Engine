#pragma once
#include "Core.h"
#include "Vector2.h"


class MouseInput
{
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

	MouseInput();
	~MouseInput() {}
	static MouseInput * instance() { return sm_instance; }

	bool IsPressed(Button btn) { return m_pressed[btn]; }
	const Vector2 & GetPos() { return m_pos; }
	Vector2 GetPosInMap();
	const Vector2 & GetDiff() { return m_diff; }
	int GetWheel() { return m_wheel; }

	const Button & GetButton() { return m_button; }
	const State & GetState() { return m_state; }
	int GetClicks() { return m_clicks; }

	void ResetDiffs() 
	{
		m_diff.x = 0; m_diff.y = 0; 
		m_wheel = 0; m_state = MOUSE_BUTTON_UNDEFINED;
	}

	void Update(SDL_Event * e);
private:
	Button					m_button;
	State					m_state;
	int						m_clicks;

	Vector2					m_pos;
	Vector2					m_diff;
	bool					m_pressed[6];

	int						m_wheel;

	static MouseInput	  * sm_instance;
};