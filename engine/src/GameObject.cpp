#include "include/GameObject.h"
#include "include/Camera.h"




GameObject::GameObject()
	: m_visible(true)
	, m_enabled(true)
	, m_position(0, 0)
	, m_angle(0)
	, m_rect({ 0, 0, 0, 0 })
	, m_color({ 255, 255, 255, 255 })
	, m_animationEnabled(false)
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
	, m_animationEnabled(false)
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
			m_sizeCoef = { 1,1 };
			
			m_center = Vector2(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
			m_texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
			SDL_FreeSurface(surface);
			return;
		}
	}
	throw std::exception();
}

void GameObject::SetAnimationEnable(bool anim, int animCount)
{
	if (m_animationEnabled == anim || animCount < 1)
	{
		return;
	}
	
	m_animationEnabled = anim;
	m_animationIndex = 0;
	
	if (m_animationEnabled)
	{
		m_size.y = static_cast<int>(m_rect.w / animCount);
		m_animationCount = animCount;
	}
	else
	{
		m_size = { m_rect.w, m_rect.h };
		m_animationCount = 1;
	}
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
	if (m_rect.w != size.x && m_rect.h != size.y)
	{
		m_size = size;
		m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
		m_center = Vector2(m_position.x + m_rect.w / 2, m_position.y + m_rect.h / 2);

		if (m_animationEnabled)
		{
			m_size.y = static_cast<int>(m_rect.w / m_animationCount);
		}
	}
}

void GameObject::UpdatePos(const Vector2 & pos)
{
	if (m_position != pos)
	{
		m_position = pos;
		m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
		m_center = Vector2(m_position.x + m_rect.w / 2, m_position.y + m_rect.h / 2);
	}
}

void GameObject::Update(float dt)
{
	if (m_animationEnabled)
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
}

void GameObject::Render()
{
	if (IsVisible()) 
	{
		SDL_Rect localRect = m_rect;

		// Apply camera moving
		localRect.x = localRect.x + Camera::instance()->GetDiff().x;
		localRect.y = localRect.y + Camera::instance()->GetDiff().y;

		// Apply zoom
		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		SDL_Rect * animRect = nullptr;
		
		if (m_animationEnabled)
		{
			animRect->x = m_size.x * m_animationIndex;
			animRect->y = 0;
			animRect->w = m_size.x;
			animRect->h = m_size.y;
		}

		SDL_RenderCopy(m_renderer, m_texture, animRect, &localRect);
	}
}
