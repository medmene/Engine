#include "sGameObject.h"
#include <utility>
#include "Geometry.h"
#include "Property.h"
#include "Renderer.h"
#include "sGameObjectDisplay.h"


sGameObject::sGameObject(sGameObject* parent)
{
	m_parent = parent;
	m_geometry = make_shared<Geometry>();
	m_properties = make_shared<Property>();
	if (parent)
	{
		m_groupId = parent->m_groupId;
		SetRenderer(parent->m_renderer->m_renderer);
	}
	else
	{
		m_groupId = 0;
	}
}

sGameObject::~sGameObject()
{
	
}

shared_ptr<Geometry> sGameObject::GetGeometry()
{
	return m_geometry;
}

shared_ptr<Property> sGameObject::GetProperties()
{
	return m_properties;
}

shared_ptr<Renderer> sGameObject::GetRenderer()
{
	return m_renderer;
}

shared_ptr<sGameObjectDisplay> sGameObject::GetObjectDisplay()
{
	return m_display;
}

int sGameObject::GetGroupId()
{
	return m_groupId;
}

void sGameObject::SetObjectDisplay(shared_ptr<sGameObjectDisplay> objectDisplay)
{
	m_display = std::move(objectDisplay);
}

void sGameObject::SetRenderer(SDL_Renderer* renderer)
{
	m_renderer = make_shared<Renderer>(this, renderer);
}

sGameObject* sGameObject::GetParent()
{
	return m_parent;
}
