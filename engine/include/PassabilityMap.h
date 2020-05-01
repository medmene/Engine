#pragma once
#include "Core.h"
#include "ResourceManager.h"
#include "Vector2.h"

struct PassabilityNode
{
	PassabilityNode(const Vector2 & pos, const Vector2 & size, bool passible);
	Vector2		m_pos;
	Vector2		m_size;
	bool		m_passible;
	SDL_Rect	m_rect;
	bool IsInside(const Vector2 & pos);
	void UpdateRect();
};


class PassabilityMap
{
public:
	PassabilityMap();
	~PassabilityMap();

	static PassabilityMap * instance() { return sm_instance; }
	void Init(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	
	void SaveMap();
	
	void Update();
	void Render();
private:
	Resource						  * m_resource = nullptr;
	SDL_Renderer					  * m_renderer = nullptr;
	bool								m_editMode = false;

	vector<PassabilityNode *>			m_nodes;
	
	static PassabilityMap			  * sm_instance;
};
