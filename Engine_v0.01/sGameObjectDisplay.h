#pragma once
#include "Core.h"

class sGameObject;

class sGameObjectDisplay
{
public:
	sGameObjectDisplay(sGameObject * object, const string& path);
	sGameObjectDisplay(sGameObject * object, SDL_Surface * surface);	
	~sGameObjectDisplay(); 

	SDL_Texture * GetTexture() { return m_texture; }
			
private:
	SDL_Texture 			  * m_texture;
	sGameObject				  * m_object;

	string						m_resourceName;
};

