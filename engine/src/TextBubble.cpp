#include "include/TextBubble.h"
#include "include/Camera.h"
#include "include/Animator.h"
#include "pugixml/pugixml.hpp"


TextBubble::TextBubble(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: GameObject(renderer, src, type)
{
	m_currentSide = RIGHT;

	if (m_resourceSettings)
	{
		pugi::xml_document doc;
		doc.load_file(m_resourceSettings->GetPath().c_str());
		auto rootNode = doc.child("object");

		auto sizeNode = rootNode.child("relativePos");
		int x = std::stoi(sizeNode.attribute("x").value());
		int y =  std::stoi(sizeNode.attribute("y").value());
		m_defaultRelPos = Vector2(x, y);
	}
}

void TextBubble::SetSide(Side s)
{
	if (m_currentSide != s)
	{
		m_currentSide = s;
		auto pos = GetRelativePos();
		switch (m_currentSide)
		{
		case LEFT:
			pos.x = -m_defaultRelPos.x;
			pos.y = -m_defaultRelPos.y;
			break;
		case RIGHT:
			pos.x = m_defaultRelPos.x;
			pos.y = -m_defaultRelPos.y;
			break;
		}
		UpdateRelativePos(pos);
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
