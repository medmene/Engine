#include "include/TextBubble.h"
#include "include/Camera.h"
#include "include/Animator.h"


TextBubble::TextBubble(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: GameObject(renderer, src, type)
{
	m_currentSide = RIGHT;
}

void TextBubble::SetSide(Side s)
{
	if (m_currentSide != s)
	{
		if (auto parent = GetParent())
		{
			m_currentSide = s;
			auto pos = parent->GetSize();
			switch (m_currentSide)
			{
			case LEFT:
				pos = Vector2(-pos.x / 2, -pos.y / 2);
				break;
			case RIGHT:
				pos = Vector2(pos.x / 2, -pos.y / 2);
				break;
			}
			UpdateRelativePos(pos);
		}
	}
}

void TextBubble::Update(float dt)
{
	GameObject::Update(dt);
}

void TextBubble::Render()
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

		switch (m_currentSide)
		{
		case LEFT:
			m_animator->GetActiveAnimation()->SetState(1);
			break;
		case RIGHT:
			m_animator->GetActiveAnimation()->SetState(0);
			break;
		}

		// SDL_Rect a = m_animator->GetActiveAnimation()->GetCurrentState();
		SDL_RenderCopy(m_renderer, m_texture, &m_animator->GetActiveAnimation()->GetCurrentState(), &localRect);
	}
}
