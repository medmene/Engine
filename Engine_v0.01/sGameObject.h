#pragma once
#include "Core.h"

class Geometry;
class Property;
class Renderer;
class sGameObjectDisplay;

class sGameObject
{
public:
	sGameObject(sGameObject * parent);
	~sGameObject();
	
	sGameObject * GetParent();

	shared_ptr<Geometry> GetGeometry();
	shared_ptr<Property> GetProperties();
	shared_ptr<Renderer> GetRenderer();
	shared_ptr<sGameObjectDisplay> GetObjectDisplay();
	int GetGroupId();
	void SetGroupId(int id) { m_groupId = id; }
	
	void SetObjectDisplay(shared_ptr<sGameObjectDisplay> objectDisplay);
	void SetRenderer(SDL_Renderer * renderer);
private:
	sGameObject						  * m_parent;
	
	shared_ptr<Geometry>				m_geometry;
	shared_ptr<Property>				m_properties;
	shared_ptr<sGameObjectDisplay>		m_display;

	unsigned							m_groupId;

	shared_ptr<Renderer>				m_renderer;
	friend class sGameObjectDisplay;
	friend class Renderer;
};

