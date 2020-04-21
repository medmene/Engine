#include "include/GameObject.h"
#include "include/Camera.h"




GameObject::GameObject()
	: m_visible(true)
	, m_enabled(true)
	, m_position(0, 0)
	, m_angle(0)
	, m_animationCount(1)
	, m_animationIndex(0)
	, m_animationFrameTime(0.2f)
	, m_rect({ 0, 0, 0, 0 })
	, m_color({ 255, 255, 255, 255 })
{
}

GameObject::~GameObject()
{
	if (m_texture) 
	{
		SDL_DestroyTexture(m_texture);
	}
}

GameObject::GameObject(SDL_Renderer * renderer, const string & src, ResourceManager::Type type)
	: m_visible(true)
	, m_enabled(true)
	, m_position(0, 0)
	, m_angle(0)
	, m_animationIndex(0)
	, m_animationFrameTime(0.2f)
{
	m_renderer = renderer;
	m_resource = ResourceManager::instance()->GetResource(src, type);
	
	if (m_resource)
	{
		auto surface = IMG_Load(m_resource->GetPath().c_str());
		
		if (surface)
		{
			m_rect = surface->clip_rect;
			m_size = { m_rect.w, m_rect.h };
			//m_animationCount =  // TODO made this
			m_center = Vector2(m_position.x + m_rect.w / 2, m_position.y + m_rect.h / 2);
			m_texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
			SDL_FreeSurface(surface);
			return;
		}
	}
	throw std::exception();
}

void GameObject::UpdateColor(const Color & clr)
{
	m_color = clr;
	if (m_texture)
	{
		SDL_SetTextureColorMod(m_texture, m_color.GetR(), m_color.GetG(), m_color.GetB());
		SDL_SetTextureAlphaMod(m_texture, m_color.GetA());
	}
}

void GameObject::UpdateSize(const Vector2 & size)
{
	m_size = size;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = Vector2(m_position.x + m_rect.w / 2, m_position.y + m_rect.h / 2);
}

void GameObject::UpdatePos(const Vector2 & pos)
{
	m_position = pos;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = Vector2(m_position.x + m_rect.w / 2, m_position.y + m_rect.h / 2);
}

void GameObject::Update(float dt)
{
	m_counter += dt;
	if (m_counter > m_animationFrameTime)
	{
		m_animationIndex++;
		m_counter = 0;
	}
	if (m_animationIndex >= m_animationCount)
	{
		m_animationIndex = 0;
	}
}

void GameObject::Draw()
{
	if (IsVisible()) 
	{
		SDL_Rect localRect = GetRenderRect();

		localRect.x = localRect.x + Camera::instance()->GetDiff().x;
		localRect.y = localRect.y + Camera::instance()->GetDiff().y;

		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		SDL_Rect animRect;


		SDL_RenderCopy(m_renderer, m_texture, nullptr, &localRect);
	}
}
