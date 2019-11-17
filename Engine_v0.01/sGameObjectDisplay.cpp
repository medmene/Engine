#include "sGameObjectDisplay.h"
#include "sGameObject.h"
#include "Renderer.h"




sGameObjectDisplay::sGameObjectDisplay(sGameObject* object, const string& path)
{
	m_surface = IMG_Load(path.c_str());
	m_resourceName = path;
	m_object = object;
	if (m_surface)
	{
		m_texture = SDL_CreateTextureFromSurface(m_object->m_renderer->m_renderer, m_surface);
	}
}

sGameObjectDisplay::sGameObjectDisplay(sGameObject* object, SDL_Surface* surface)
{
	m_surface = surface;
	m_resourceName = "";
	m_object = object;
	if (m_surface)
	{
		m_texture = SDL_CreateTextureFromSurface(m_object->m_renderer->m_renderer, m_surface);
	}
}

sGameObjectDisplay::~sGameObjectDisplay()
{
	if (m_surface)
	{
		SDL_FreeSurface(m_surface);
	}
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}
