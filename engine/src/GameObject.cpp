#include "include/GameObject.h"
#include "include/Camera.h"
#include "pugixml/pugixml.hpp"
#include "include/Animator.h"
#include "include/Event.h"
#include "include/EventManager.h"
#include "include/Reaction.h"



GameObject::GameObject()
	: m_rect({ 0, 0, 0, 0 })
	, m_center(0, 0)
	, m_relativePos(0, 0)
	, m_color({ 255, 255, 255, 255 })
	, m_position(0, 0)
	, m_size(0, 0)
	, m_visible(true)
	, m_staticObject(false)
{
}

bool GameObject::CreateSettings(const string & src, ResourceManager::Type type)
{
	m_resourceTexture = ResourceManager::instance()->GetResource(src, type);
	if (m_resourceTexture)
	{
		if (m_resourceTexture)
		{
			auto surface = IMG_Load(m_resourceTexture->GetPath().c_str());

			if (surface)
			{
				m_rect = surface->clip_rect;
				m_size = { m_rect.w, m_rect.h };

				m_center = Vector2(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
				m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
				SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
				SDL_FreeSurface(surface);
			}
		}

		string newResName = m_resourceTexture->GetName() + "_settings";
		m_resourceSettings = ResourceManager::instance()->CreateResourceFile(
			m_resourceTexture->GetDir(), newResName, ResourceManager::GOBJECT);

		if (m_resourceSettings)
		{
			pugi::xml_document doc;
			doc.load_file(m_resourceSettings->GetPath().c_str());

			pugi::xml_node rootNode = doc.child("object");

			// Node 1. - texture
			auto sourceNode = rootNode.append_child("source");
			sourceNode.append_attribute("name") = (m_resourceTexture->GetName()
				+ ResourceManager::instance()->GetType(m_resourceTexture->GetType())).c_str();

			// Node 2. - size
			auto objSizeChild = rootNode.append_child("objSize");
			objSizeChild.append_attribute("x") = std::to_string((int)m_size.x).c_str();
			objSizeChild.append_attribute("y") = std::to_string((int)m_size.y).c_str();
			objSizeChild.append_attribute("annotation") = "This is size for saving";

			// Node 3. - size
			auto animSizeChild = rootNode.append_child("animSize");
			animSizeChild.append_attribute("x") = std::to_string((int)m_size.x).c_str();
			animSizeChild.append_attribute("y") = std::to_string((int)m_size.y).c_str();
			animSizeChild.append_attribute("annotation") = "This is size of real frame in image";

			// Node 4. - default animation
			auto node = rootNode.append_child("animation");
			node.append_attribute("name") = "default";
			node.append_attribute("row") = "0";
			node.append_attribute("count") = 1;
			node.append_attribute("loop") = "true";
			node.append_attribute("speed") = 100;
			node.append_attribute("next_state") = "";

			doc.save_file(m_resourceSettings->GetPath().c_str());

			m_animator = new Animator(&doc);
			return true;
		}
	}
	return false;
}

bool GameObject::LoadSettings(const string & src, ResourceManager::Type type)
{
	m_resourceSettings = ResourceManager::instance()->GetResource(src, type);

	if (m_resourceSettings)
	{
		return LoadSettings();
	}
	return false;
}

bool GameObject::LoadSettings()
{
	pugi::xml_document doc;
	doc.load_file(m_resourceSettings->GetPath().c_str());
	auto rootNode = doc.child("object");

	auto sizeNode = rootNode.child("objSize");
	m_size.x = std::stoi(sizeNode.attribute("x").value());
	m_size.y = std::stoi(sizeNode.attribute("y").value());

	auto sourceNode = rootNode.child("source");
	m_resourceTexture = ResourceManager::instance()->GetResource(sourceNode.attribute("name").value());

	if (m_resourceTexture)
	{
		m_animator = new Animator(&doc);

		auto surface = IMG_Load(m_resourceTexture->GetPath().c_str());

		if (surface)
		{
			m_rect = { 0,0, (int)m_size.x, (int)m_size.y };

			m_center = Vector2(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
			m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
			SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
			SDL_FreeSurface(surface);
			return true;
		}
	}
	return false;
}

GameObject::GameObject(SDL_Renderer * renderer, const string & src, ResourceManager::Type type)
	: m_position(0, 0)
	, m_relativePos(0, 0)
	, m_visible(true)
	, m_staticObject(false)
{
	m_renderer = renderer;

	if (type != ResourceManager::GOBJECT)
	{
		// Try to find resource with settings
		m_resourceSettings = ResourceManager::instance()->GetResource(src + "_settings", ResourceManager::GOBJECT);
		if (!m_resourceSettings)
		{
			// If trying loading gameObject without .gobj res
			// Create it
			if (CreateSettings(src, type))
			{
				return;
			}
		}
		else
		{
			if (LoadSettings())
			{
				return;
			}
		}
	}
	else if (LoadSettings(src, type))
	{
		return;
	}
	throw std::exception("Can't load resource!");
}

GameObject::~GameObject()
{
	if (m_texture) { SDL_DestroyTexture(m_texture); }
	if (m_animator) { delete m_animator; }
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
	if (m_resourceSettings)
	{
		return m_resourceSettings->GetName();
	}
	return "";
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

void GameObject::UpdateCenterPos(const Vector2& pos)
{
	if (m_center != pos)
	{
		m_position = Vector2(pos.x - m_size.x / 2, pos.y - m_size.y / 2);
		m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
		m_center = pos;
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
		m_staticObject = m_parent->IsStaticObject();
		UpdateCenterPos(m_parent->GetCenterPos() + m_relativePos);
		m_visible = m_parent->IsVisible();
	}
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

void GameObject::Subscribe(Event* e, function<void(GameObject*,Event*)> callback)
{
	EventManager::instance()->RegisterEvent(e, new Reaction(this, callback));
}