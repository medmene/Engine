#include "include/game_object/GameObject.h"
#include "include/input/Camera.h"
#include "pugixml/pugixml.hpp"
#include "include/controller/Animator.h"
#include "include/controller/ResourceManager.h"
#include "include/tools/Utils.h"


GameObject::GameObject()
	: BaseObject()
	, m_name("empty")
	, m_rect({ 0, 0, 0, 0 })
	, m_center(0, 0)
	, m_color({ 255, 255, 255, 255 })
	, m_position(0, 0)
	, m_relativePos(0, 0)
	, m_size(0, 0)
	, m_pivot(0, 0)
	, m_pivotOffset(0, 0)
	, m_visible(true)
	, m_staticObject(false)
	, m_followVisibility(false)
	, m_followStatic(false)
{
}

GameObject::GameObject(const string & name)
	: BaseObject()
	, m_name(name)
	, m_rect({ 0, 0, 0, 0 })
	, m_center(0, 0)
	, m_color({ 255, 255, 255, 255 })
	, m_position(0, 0)
	, m_relativePos(0, 0)
	, m_size(0, 0)
	, m_pivot(0, 0)
	, m_pivotOffset(0, 0)
	, m_visible(true)
	, m_staticObject(false)
	, m_followVisibility(false)
	, m_followStatic(false)
{
}

void GameObject::LoadSettings(pugi::xml_node * node)
{
	// Name
	if (!node->attribute("name").empty())
	{
		m_name = node->attribute("name").value();
	}

	// Static
	if (!node->attribute("static").empty())
	{
		string val = node->attribute("static").value();
		m_staticObject = val == "true";
	}

	// Visible
	if (!node->attribute("visible").empty())
	{
		string val = node->attribute("visible").value();
		m_visible = val == "true";
	}

	// Follow visability
	if (!node->attribute("follow_visible").empty())
	{
		string val = node->attribute("follow_visible").value();
		m_followVisibility = val == "true";
	}

	// Follow static
	if (!node->attribute("follow_static").empty())
	{
		string val = node->attribute("follow_static").value();
		m_followStatic = val == "true";
	}

	// Source
	if (!node->attribute("source").empty())
	{
		m_resourceTexture = ResourceManager::instance()->GetResource(node->attribute("source").value());
	}

	// Pivot offset
	if (!node->attribute("pivot_offset").empty())
	{
		auto tokens = Utils::split(node->attribute("pivot_offset").value(), " ");
		m_pivotOffset.x = std::stoi(tokens[0]);
		m_pivotOffset.y = std::stoi(tokens[1]);
	}

	// Relative position
	if (!node->attribute("relative_position").empty())
	{
		auto tokens = Utils::split(node->attribute("relative_position").value(), " ");
		m_relativePos.x = std::stof(tokens[0]);
		m_relativePos.y = std::stof(tokens[1]);
	}

	// Color
	if (!node->attribute("color").empty())
	{
		auto tokens = Utils::split(node->attribute("color").value(), " ");
		m_color.SetR(std::stoi(tokens[0]));
		m_color.SetG(std::stoi(tokens[1]));
		m_color.SetB(std::stoi(tokens[2]));
		m_color.SetA(std::stoi(tokens[3]));
	}

	// Size
	if (!node->attribute("object_size").empty())
	{
		auto tokens = Utils::split(node->attribute("object_size").value(), " ");
		Vector2 sz;
		sz.x = std::stoi(tokens[0]);
		sz.y = std::stoi(tokens[1]);
		UpdateSize(sz);
	}

	// Position
	if (!node->attribute("position").empty())
	{
		auto tokens = Utils::split(node->attribute("position").value(), " ");
		Vector2 pos;
		pos.x = std::stof(tokens[0]);
		pos.y = std::stof(tokens[1]);
		UpdatePos(pos);
	}
}

void GameObject::LoadGraphics(pugi::xml_node * node)
{
	LoadSettings(node);

	if (m_resourceTexture)
	{
		m_animator = new Animator(node);
		auto surface = IMG_Load(m_resourceTexture->GetPath().c_str());

		if (surface)
		{
			UpdatePos(GetPosition());
			m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
			SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
			SDL_FreeSurface(surface);
			return;
		}
	}
	throw std::exception("Can't load resource!");
}

GameObject::~GameObject()
{
	if (m_texture) { SDL_DestroyTexture(m_texture); }
	delete m_animator;
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

string GameObject::GetName()
{
	return m_name;
}

void GameObject::UpdateColor(const Color & clr)
{
	if (m_color != clr)
	{
		m_color = clr;
		if (m_texture)
		{
			SDL_SetTextureColorMod(m_texture, m_color.GetR(), m_color.GetG(), m_color.GetB());
			SDL_SetTextureAlphaMod(m_texture, m_color.GetA());
		}
	}
}

void GameObject::UpdateSize(const Vector2 & size)
{
	if (m_size != size)
	{
		m_size = size;
		m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
		m_center = Vector2(m_position.x + m_rect.w / 2, m_position.y + m_rect.h / 2);
		m_pivot = m_center + m_pivotOffset;
	}
}

void GameObject::UpdatePos(const Vector2 & pos)
{
	if (m_position != pos)
	{
		m_position = pos;
		m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
		m_center = Vector2(m_position.x + m_rect.w / 2, m_position.y + m_rect.h / 2);
		m_pivot = m_center + m_pivotOffset;
	}
}

void GameObject::UpdateCenterPos(const Vector2& pos)
{
	if (m_center != pos)
	{
		m_position = Vector2(pos.x - m_size.x / 2, pos.y - m_size.y / 2);
		m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
		m_center = pos;
		m_pivot = m_center + m_pivotOffset;
	}
}

void GameObject::UpdateRelativePos(const Vector2& pos)
{
	m_relativePos = pos;
}

void GameObject::Update(float dt)
{
	if (m_animator)
	{
		m_animator->Update(dt);
	}

	if (m_parent)
	{
		UpdateCenterPos(m_parent->GetCenterPos() + m_relativePos);
		
		if (m_followVisibility)
		{
			m_visible = m_parent->IsVisible();
		}

		if (m_followStatic)
		{
			m_staticObject = m_parent->IsStaticObject();
		}
	}
}

void GameObject::Render()
{
	if (IsVisible()) 
	{
		SDL_Rect localRect = m_rect;
		
		if (!m_staticObject)
		{
			// Apply zoom
			localRect.x *= Camera::instance()->GetZoom();
			localRect.y *= Camera::instance()->GetZoom();
			localRect.w *= Camera::instance()->GetZoom();
			localRect.h *= Camera::instance()->GetZoom();

			// Apply camera moving
			auto diff = Camera::instance()->GetDiff();
			localRect.x = localRect.x + diff.x;
			localRect.y = localRect.y + diff.y;
		}
		
		SDL_RenderCopy(m_renderer, m_texture, &m_animator->GetActiveAnimation()->GetCurrentState(), &localRect);
	}
}