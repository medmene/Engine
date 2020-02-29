#include "include\GameObject.h"

GameObject::GameObject()
	: m_visible(true)
	, m_enabled(true)
	, m_position(0, 0)
	, m_angle(0)
	, m_rect({ 0, 0, 0, 0 })
{
}

GameObject::~GameObject()
{
	if (m_texture) 
	{
		SDL_DestroyTexture(m_texture);
	}
}

GameObject::GameObject(SDL_Renderer	* renderer, string src)
	: m_visible(true)
	, m_enabled(true)
	, m_position(0, 0)
	, m_angle(0)
{
	auto surface = IMG_Load((std::filesystem::current_path().generic_string() + "/../resources/" + src).c_str());
	if (surface)
	{
		m_resourceName = src;
		m_rect = surface->clip_rect;
		m_size = { m_rect.w, m_rect.h };
		m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
		m_texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
}

const SDL_Rect & GameObject::GetRenderRect()
{
	return m_rect;
}

void GameObject::UpdateSize(const Vector2 & size)
{
	m_size = size;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
}

void GameObject::UpdatePos(const Vector2 & pos)
{
	m_position = pos;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
}
