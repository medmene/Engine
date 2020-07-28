#include "include/game_object/CheckBox.h"
#include "include/game_object/Label.h"
#include "pugixml/pugixml.hpp"
#include "include/controller/Animator.h"
#include "include/input/Camera.h"
#include "include/input/MouseInput.h"



CheckBox::CheckBox()
	: GameObject()
{
	m_onClick = [] {return false; };
}

CheckBox::CheckBox(const string & name)
	: GameObject(name)
{
	m_onClick = [] {return false; };
}

CheckBox::~CheckBox()
{
	delete m_label;
}

void CheckBox::LoadGraphics(pugi::xml_node * node)
{
	GameObject::LoadGraphics(node);
}

void CheckBox::SetText(const u16string & text)
{

}

void CheckBox::Update(float dt)
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
			m_checked = true;
		}
		else if (MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_UP)
		{
			m_checked = false;
			if (m_onClick())
			{
				return;
			}
		}
	}
}


bool CheckBox::IsMouseInside() 
{
	Vector2 mousePos = m_staticObject
		? MouseInput::instance()->GetPos()
		: MouseInput::instance()->GetPosInMap();
	
	return m_rect.x <= mousePos.x && (m_rect.x + m_rect.w) >= mousePos.x
		&& m_rect.y <= mousePos.y && (m_rect.y + m_rect.h) >= mousePos.y;
}

void CheckBox::Render()
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

		m_animator->GetActiveAnimation()->SetState(m_checked ? 1 : 0);
		SDL_RenderCopy(m_renderer, m_texture, 
			&m_animator->GetActiveAnimation()->GetCurrentState(), &localRect);

		if (m_label && m_label->IsVisible())
		{
			m_label->Render();
		}
	}
}