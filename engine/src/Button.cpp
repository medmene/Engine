#include "include/Button.h"
#include "include/Label.h"
#include "pugixml/pugixml.hpp"
#include "include/Animator.h"
#include "include\Camera.h"
#include "include\MouseInput.h"


Button::Button()
	: m_visible(true)
	, m_position(0, 0)
	, m_rect({ 0, 0, 0, 0 })
	, m_color({ 255, 255, 255, 255 })
	, m_animationEnabled(true)
{
}

Button::~Button()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

Button::Button(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: m_visible(true)
	, m_position(0, 0)
	, m_rect({ 0, 0, 0, 0 })
	, m_color({ 255, 255, 255, 255 })
	, m_animationEnabled(true)
{
	m_renderer = renderer;
	m_resource = ResourceManager::instance()->GetResource(src, type);
	
	if (type == ResourceManager::GOBJECT)
	{
		if (m_resource)
		{
			pugi::xml_document doc;
			doc.load_file(m_resource->GetPath().c_str());
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
	throw std::exception();
}

void Button::UpdatePos(const Vector2 & pos)
{
	m_position = pos;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
}

void Button::UpdateSize(const Vector2 & size)
{
	m_size = size;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
}

void Button::Update(float dt)
{
	if (IsMouseInside())
	{
		if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_DOWN)
			m_isPressed = true;
		else if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_UP)
			m_isPressed = false;
	}
}

void Button::UpdateColor(const Color & clr)
{
	// m_color = clr;
	//
	// if (m_texture)
	// {
	// 	SDL_SetTextureColorMod(m_texture, m_color.GetR(), m_color.GetG(), m_color.GetB());
	// 	SDL_SetTextureAlphaMod(m_texture, m_color.GetA());
	// }
}

bool Button::IsMouseInside() 
{
	Vector2 mpousePos = MouseInput::instance()->GetPos();
	return m_rect.x <= mpousePos.x && (m_rect.x + m_rect.w) >= mpousePos.x && m_rect.y <= mpousePos.y && (m_rect.y + m_rect.h) >= mpousePos.y;
}

void Button::Render()
{
	if (IsVisible())
	{
		SDL_Rect localRect = m_rect;

		// Apply camera moving
		if (!m_staticObject)
		{
			localRect.x = localRect.x + Camera::instance()->GetDiff().x;
			localRect.y = localRect.y + Camera::instance()->GetDiff().y;
		}

		// Apply zoom
		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();
		
		if (m_isPressed)
			m_animator->GetActiveAnimation()->SetState(1);
		else
			m_animator->GetActiveAnimation()->SetState(0);
		SDL_Rect a = m_animator->GetActiveAnimation()->GetCurrentState();
		SDL_RenderCopy(m_renderer, m_texture, &a, &localRect);
	}
}