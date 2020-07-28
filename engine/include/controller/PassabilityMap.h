#pragma once
#include "include/controller/other/Areas.h"


class Resource;
class PassabilityNode;


class PassabilityMap
{
	PassabilityMap();
public:
	/* Types:
	 * 0 - passible area
	 * 1 - impassible area
	 * 2 - trigger area
	 * 3 - slowing area
	 */
	enum AreaTypes
	{
		PASSIBLE_AREA = 0,
		IMPASSIBLE_AREA,
		TRIGGER_AREA,
		LADDER_AREA
	};
	
	~PassabilityMap();

	static PassabilityMap * instance();
	void Init(SDL_Renderer * renderer);
	void SetMap(const string & src);

	Vector2 WorldToNodeIndex(const Vector2 & pos);
	Vector2 NodeIndexToWorld(const Vector2 & pos);
	void FillPMap(vector<vector<int>> & pMap);
	
	bool IsAreaPossible(PassabilityArea * area);
	auto GetAllNodes() { return m_nodes; }
	auto GetMapSize() { return m_mapSize; }
	auto GetNodeSize() { return m_nodeSize; }
	AreaTypes GetAreaTypeInPos(const Vector2 & pos);
	
	void Update();
	void Render();
	
private:
	bool inline IsInMap(const Vector2 & pos);
	bool SaveMap();
	bool LoadMap();
	void GenerateMapTexture();
	void UpdateMapTexture(PassabilityNode * node);
	void ProcessMouse();
	
	Resource						  * m_resource = nullptr;
	SDL_Renderer					  * m_renderer = nullptr;
	SDL_Surface						  * m_mapSurface = nullptr;
	SDL_Texture						  * m_mapTexture = nullptr;
	bool								m_editMode = false;
	Vector2								m_mapSize;
	Vector2								m_nodeSize;
	Vector2								m_indexOffset;
	

	vector<vector<PassabilityNode *>>	m_nodes;
	
	static PassabilityMap			  * sm_instance;
};

void SDL_DrawCircle(SDL_Renderer * renderer, const Vector2& centre, int32_t radius);

class PassabilityNode
{
public:
	PassabilityNode(const Vector2 & pos, const Vector2 & size, PassabilityMap::AreaTypes type);
	bool IsInside(const Vector2 & pos);
	void UpdateRect();
	Vector2 GetSize() { return m_size; }
	Vector2 GetPos() { return m_pos; }
	PassabilityMap::AreaTypes GetType() { return m_type; }
	SDL_Rect GetRenderRect() { return m_rect; }
	void SetType(PassabilityMap::AreaTypes tp) { m_type = tp; }
	
private:
	Vector2							m_pos;
	Vector2							m_size;
	PassabilityMap::AreaTypes		m_type;
	SDL_Rect						m_rect;
};