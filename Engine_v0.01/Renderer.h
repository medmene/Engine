#pragma once
#include  "Core.h"

class sGameObject;
class sGameObjectDisplay;

class Renderer
{
public:
	Renderer(sGameObject * object, SDL_Renderer * renderer);
	~Renderer();

	void render();	
private:
	SDL_Renderer					  * m_renderer;
	sGameObject						  * m_object;
	friend class sGameObjectDisplay;
	friend class sGameObject;
};

