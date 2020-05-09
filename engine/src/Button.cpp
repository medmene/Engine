#include "include/Button.h"
#include "include/Label.h"
#include "pugixml/pugixml.hpp"
#include "include/Animator.h"
#include "include\Camera.h"
#include "include\MouseInput.h"


Button::Button()
	: GameObject()
{
	m_onClick = [] {return false; };
}

Button::Button(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: GameObject(renderer, src, type)
{
	m_renderer = renderer;
	m_onClick = [] {return false; };
}

Button::~Button()
{
	delete m_label;
}

void Button::SetLabel(const string& text, int textFontSize, const string& src, ResourceManager::Type type)
{
	m_label = new Label(m_renderer, "times", ResourceManager::TTF);
	if (m_label)
	{
		m_label->SetVisible(true);
		m_label->SetFontSize(textFontSize);
		m_label->SetStaticObject(IsStaticObject());
		m_label->SetText(text);
		m_label->SetParent(this);
	}
}

void Button::Update(float dt)
{
	GameObject::Update(dt);
	if (m_label && m_label->IsVisible())
	{
		m_label->Update(dt);
	}

	if (IsMouseInside())
	{
		if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_DOWN)
		{
			m_isPressed = true;
		}
		else if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_UP)
		{
			m_isPressed = false;
			if (m_onClick())
			{
				return;
			}
		}
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
			// Apply zoom
			localRect.x *= Camera::instance()->GetZoom();
			localRect.y *= Camera::instance()->GetZoom();
			localRect.w *= Camera::instance()->GetZoom();
			localRect.h *= Camera::instance()->GetZoom();
			
			auto diff = Camera::instance()->GetDiff();
			localRect.x = localRect.x + diff.x;
			localRect.y = localRect.y + diff.y;
		}

		m_animator->GetActiveAnimation()->SetState(m_isPressed ? 1 : 0);
		SDL_RenderCopy(m_renderer, m_texture, 
			&m_animator->GetActiveAnimation()->GetCurrentState(), &localRect);

		if (m_label && m_label->IsVisible())
		{
			m_label->Render();
		}
	}
}