#include "include/Button.h"
#include "include/Label.h"
#include "pugixml/pugixml.hpp"
#include "include/Animator.h"
#include "include\Camera.h"
#include "include\MouseInput.h"


Button::Button()
	: GameObject()
{
	m_onClick = [] {};
}

Button::Button(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: GameObject(renderer, src, type)
{
	m_renderer = renderer;
	m_onClick = [] {};
}

void Button::SetLabel(const string& text, const string& src, ResourceManager::Type type)
{
	m_label = new Label(m_renderer, src, type);
	if (m_label)
	{
		m_label->SetStaticObject(IsStaticObject());
		m_label->SetText(text);
		m_label->UpdatePos(m_position);
		m_label->UpdateSize(m_size);
	}
}

void Button::Update(float dt)
{
	if (IsMouseInside())
	{
		if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_DOWN)
		{
			m_isPressed = true;
		}
		else if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_UP)
		{
			m_onClick();
			m_isPressed = false;
		}
	}
	
	GameObject::Update(dt);
	if (m_label)
	{
		m_label->Update(dt);
	}
}


bool Button::IsMouseInside() 
{
	Vector2 mousePos = m_staticObject
		? MouseInput::instance()->GetPos()
		: MouseInput::instance()->GetPosInMap();
	
	return m_rect.x <= mousePos.x && (m_rect.x + m_rect.w) >= mousePos.x
		&& m_rect.y <= mousePos.y && (m_rect.y + m_rect.h) >= mousePos.y;
}

void Button::Render()
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
		
		if (m_isPressed)
		{
			m_animator->GetActiveAnimation()->SetState(1);
		}
		else
		{
			m_animator->GetActiveAnimation()->SetState(0);
		}
		
		SDL_Rect a = m_animator->GetActiveAnimation()->GetCurrentState();
		SDL_RenderCopy(m_renderer, m_texture, &a, &localRect);

		if (m_label)
		{
			m_label->Render();
		}
	}
}