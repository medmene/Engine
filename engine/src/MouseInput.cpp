#include "include/MouseInput.h"



MouseInput * MouseInput::sm_instance = new MouseInput();

MouseInput::MouseInput()
	: m_pos(0, 0)
	, m_clicks(0)
	, m_diff(0, 0)
	, m_wheel(0)
{
	m_button = MOUSE_UNDEFINED;
	m_state = MOUSE_BUTTON_UNDEFINED;
	for (int i = 0; i < 6; ++i)
	{
		m_pressed[i] = false;
	}
}

void MouseInput::Update(SDL_Event * e)
{
	switch (e->type)
	{
	case SDL_MOUSEMOTION:
	{
		Vector2 tmp(e->motion.x, e->motion.y);
		m_diff = tmp - m_pos;
		m_pos = tmp;
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		m_pos.x = e->button.x;
		m_pos.y = e->button.y;
		m_button = (Button)(e->button.button - 1);
		m_pressed[m_button] = true;
		m_state = MOUSE_BUTTON_DOWN;
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		m_pos.x = e->button.x;
		m_pos.y = e->button.y;
		m_clicks = e->button.clicks;
		m_button = (Button)(e->button.button - 1);
		m_pressed[m_button] = false;
		m_state = MOUSE_BUTTON_UP;
		break;
	}
	case SDL_MOUSEWHEEL:
	{
		m_wheel = e->wheel.y;
		break;
	}
	default:
		break;
	}
}
