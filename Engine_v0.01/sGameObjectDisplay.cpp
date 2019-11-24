#include "sGameObjectDisplay.h"
#include "sGameObject.h"
#include "Renderer.h"




sGameObjectDisplay::sGameObjectDisplay(sGameObject* object, const string& path)
{
	auto surface = IMG_Load(path.c_str());
	m_resourceName = path;
	m_object = object;
	if (surface)
	{
		m_texture = SDL_CreateTextureFromSurface(m_object->m_renderer->m_renderer, surface);
		SDL_FreeSurface(surface);
	}
}

sGameObjectDisplay::sGameObjectDisplay(sGameObject* object, SDL_Surface* surface)
{
	m_resourceName = "";
	m_object = object;
	if (surface)
	{
		m_texture = SDL_CreateTextureFromSurface(m_object->m_renderer->m_renderer, surface);
	}
}

sGameObjectDisplay::~sGameObjectDisplay()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}
