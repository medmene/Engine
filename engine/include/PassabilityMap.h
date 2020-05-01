#pragma once
#include "Core.h"
#include "ResourceManager.h"
#include "Vector2.h"

struct PassabilityNode
{
	Vector2		m_pos;
	Vector2		m_size;
	bool		m_passible;
	SDL_Rect	m_rect;
	
	PassabilityNode(const Vector2 & pos, const Vector2 & size, bool passible);
	bool IsInside(const Vector2 & pos);
	void UpdateRect();
};

struct PassabilityArea
{
	Vector2		m_pos;
	float		m_radius;
	
	PassabilityArea();
	PassabilityArea(const Vector2 & pos, float rad);

	void UpdatePos(const Vector2 & pos) { m_pos = pos; }
};

class PassabilityMap
{
public:
	PassabilityMap();
	~PassabilityMap();

	static PassabilityMap * instance() { return sm_instance; }
	void Init(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	void SaveMap();

	bool IsAreaPossible(PassabilityArea * area);
	
	void Update();
	void Render();
private:
	Resource						  * m_resource = nullptr;
	SDL_Renderer					  * m_renderer = nullptr;
	bool								m_editMode = false;
	Vector2								m_mapSize;

	vector<vector<PassabilityNode *>>	m_nodes;
	
	static PassabilityMap			  * sm_instance;
};


void SDL_DrawCircle(SDL_Renderer * renderer, const Vector2& centre, int32_t radius);
