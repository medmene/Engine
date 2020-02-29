#include "include/KeyboardInput.h"

KeyboardInput::KeyboardInput()
{
}

void KeyboardInput::Update(SDL_Event * e)
{
	switch (e->type) 
	{
	case SDL_KEYDOWN:
		break;
	case SDL_KEYUP:
		break;
	case SDL_TEXTEDITING:
		break;
	case SDL_TEXTINPUT:
		break;
	// System?
	case SDL_KEYMAPCHANGED:
		break;
	}
}
