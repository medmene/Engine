#include "include/GameObject.h"
#include "include/Camera.h"
#include "pugixml/pugixml.hpp"
#include "include/Animator.h"



GameObject::GameObject()
	: m_visible(true)
	, m_staticObject(false)
	, m_position(0, 0)
	, m_gravityValue(0, 0.1f)
	, m_rect({ 0, 0, 0, 0 })
	, m_color({ 255, 255, 255, 255 })
{
}

GameObject::GameObject(SDL_Renderer * renderer, const string & src, ResourceManager::Type type)
	: m_visible(true)
	, m_staticObject(false)
	, m_position(0, 0)
	, m_gravityValue(0, 0.1f)
{
	m_renderer = renderer;
	if (type == ResourceManager::GOBJECT)
	{
		m_resourceSettings = ResourceManager::instance()->GetResource(src, type);

		if (m_resourceSettings)
		{
			pugi::xml_document doc;
			doc.load_file(m_resourceSettings->GetPath().c_str());
			auto rootNode = doc.child("object");

			auto sizeNode = rootNode.child("size");
			m_size.x = std::stoi(sizeNode.attribute("x").value());
			m_size.y = std::stoi(sizeNode.attribute("y").value());

			auto sourceNode = rootNode.child("source");
			m_resourceTexture = ResourceManager::instance()->GetResource(sourceNode.attribute("name").value());

			if (m_resourceTexture)
			{
				m_animator = new Animator(&doc, this);

				auto surface = IMG_Load(m_resourceTexture->GetPath().c_str());

				if (surface)
				{
					m_rect = { 0,0, (int)m_size.x, (int)m_size.y };

					m_center = Vector2(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
					m_texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
					SDL_FreeSurface(surface);
					return;
				}
			}
		}
	}
	else
	{
		m_resourceTexture = ResourceManager::instance()->GetResource(src, type);
	
		if (m_resourceTexture)
		{
	
			auto surface = IMG_Load(m_resourceTexture->GetPath().c_str());
	
			if (surface)
			{
				m_rect = surface->clip_rect;
				m_size = { m_rect.w, m_rect.h };

				m_animator = new Animator(this);
	
				m_center = Vector2(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
				m_texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
				SDL_FreeSurface(surface);
				return;
			}
		}
	}
	throw std::exception();
}

GameObject::~GameObject()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

bool GameObject::IsAnimationEnabled()
{
	return m_animator->IsAnimationsEnabled();
}

void GameObject::SetAnimationEnable(bool anim)
{
	if (m_animator->IsAnimationsEnabled() == anim)
	{
		return;
	}

	m_animator->SetAnimationsEnabled(anim);
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
	m_animator->Update(dt);
	
	// if (m_gravity)
	// {
	// 	UpdatePos(m_position + m_gravityValue);
	// }
}

void GameObject::Render()
{
	if (IsVisible()) 
	{
		SDL_Rect localRect = m_rect;

		// Apply camera moving
		if (!m_staticObject)
		{
			auto diff = Camera::instance()->GetDiff();
			localRect.x = localRect.x + diff.x;
			localRect.y = localRect.y + diff.y;
		}
		
		// Apply zoom
		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		SDL_RenderCopy(m_renderer, m_texture, &m_animator->GetActiveAnimation()->GetCurrentState(), &localRect);
	}
}
