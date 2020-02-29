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
		MOUSE_UNDEFINED = 100
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

	const Vector2 & GetPos() { return m_pos; }
	const Button & GetButton() { return m_button; }
	const State & GetState() { return m_state; }
	int GetClicks() { return m_clicks; }

	void Update(SDL_Event * e);
private:
	Button				m_button;
	State				m_state;
	Vector2				m_pos;
	int					m_clicks;

	static MouseInput * sm_instance;
};