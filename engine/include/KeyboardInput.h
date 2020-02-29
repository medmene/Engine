#pragma once
#include "Core.h"
#include "Vector2.h"


class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();
	static KeyboardInput * instance() { return sm_instance; }



	void Update(SDL_Event * e);

private:
	vector<int>					m_pressed;



	static KeyboardInput * sm_instance;
};