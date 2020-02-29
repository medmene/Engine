#include "include/MouseInput.h"



MouseInput * MouseInput::sm_instance = new MouseInput();

MouseInput::MouseInput()
	: m_pos(0, 0)
	, m_clicks(0)
{
	m_button = MOUSE_UNDEFINED;
	m_state = MOUSE_BUTTON_UNDEFINED;
}

void MouseInput::Update(SDL_Event * e)
{
	switch (e->type)
	{
	case SDL_MOUSEMOTION:
		m_pos.x = e->motion.x;
		m_pos.y = e->motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		m_pos.x = e->button.x;
		m_pos.y = e->button.y;
		m_button = (Button)(e->button.button - 1);
		m_state = MOUSE_BUTTON_DOWN;
		break;
	case SDL_MOUSEBUTTONUP:
		m_pos.x = e->button.x;
		m_pos.y = e->button.y;
		m_clicks = e->button.clicks;
		m_button = (Button)(e->button.button - 1);
		m_state = MOUSE_BUTTON_UP;
		break;
	case SDL_MOUSEWHEEL:
		break;
	}
}
