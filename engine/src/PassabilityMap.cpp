#include "include/PassabilityMap.h"
#include <fstream>
#include "include/Camera.h"
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"
#include "include/ResourceManager.h"


PassabilityMap * PassabilityMap::sm_instance = nullptr;

PassabilityNode::PassabilityNode(const Vector2& pos, const Vector2& size, PassabilityMap::AreaTypes type)
	: m_pos(pos)
	, m_size(size)
	, m_type(type)
{
	UpdateRect();
}

bool PassabilityNode::IsInside(const Vector2& pos)
{
	return pos.x >= m_pos.x - 0.01f && pos.x <= m_pos.x + m_size.x + 0.01f
		&& pos.y >= m_pos.y - 0.01f && pos.y <= m_pos.y + m_size.y + 0.01f;
}

void PassabilityNode::UpdateRect()
{
	m_rect = { (int)m_pos.x, (int)m_pos.y, (int)m_size.x, (int)m_size.y };
}

// --------------------------------------------------------------------------------------------- //

PassabilityMap::PassabilityMap()
	: m_mapSize(Vector2(200, 200))
	, m_nodeSize(Vector2(30, 25))
	, m_indexOffset(Vector2((int)m_mapSize.x / 2, (int)m_mapSize.y / 2))
{
}

PassabilityMap::~PassabilityMap()
{
	int stPosX = -m_indexOffset.x, endPosX = m_indexOffset.x;
	int stPosY = -m_indexOffset.x, endPosY = m_indexOffset.y;
	
	for (int x = stPosX; x < endPosX; ++x)
	{
		for (int y = stPosY; y < endPosY; ++y)
		{
			delete m_nodes[x + endPosX][y + endPosY];
		}
		m_nodes[x + endPosX].clear();
	}

	m_nodes.clear();
}

PassabilityMap* PassabilityMap::instance()
{
	if (!sm_instance)
	{
		sm_instance = new PassabilityMap();
	}
	return sm_instance;
}

void PassabilityMap::Init(SDL_Renderer * renderer)
{
	m_renderer = renderer;
}

bool PassabilityMap::SaveMap()
{
	if (m_resource)
	{
		std::ofstream out;
		out.open(m_resource->GetPath());
		
		if (out.is_open())
		{
			out << m_mapSize.x << " " << m_mapSize.y << "\n";
			
			int stPosX = -m_indexOffset.x, endPosX = m_indexOffset.x;
			int stPosY = -m_indexOffset.y, endPosY = m_indexOffset.y;
			
			for (int x = stPosX; x < endPosX; ++x)
			{
				for (int y = stPosY; y < endPosY; ++y)
				{
					PassabilityNode * nd = m_nodes[x + endPosX][y + endPosY];
					out << x + endPosX << " " << y + endPosY << " ";		// index in map same with position
					auto sz = nd->GetSize();
					out << sz.x << " " << sz.y << " ";
					out << nd->GetType();
					out << "\n";
				}
			}

			out.close();
			return true;
		}
	}
	return false;
}

bool PassabilityMap::LoadMap()
{
	if (m_resource)
	{
		std::ifstream in;
		in.open(m_resource->GetPath());

		if (in.is_open())
		{
			int tx = 0, ty = 0, sx = 0, sy = 0, p = 0;
			in >> tx >> ty; // map size

			m_mapSize = Vector2(tx, ty);
			m_indexOffset = Vector2((int)m_mapSize.x / 2, (int)m_mapSize.y / 2);

			int stPosX = -m_indexOffset.x, endPosX = m_indexOffset.x;
			int stPosY = -m_indexOffset.y;

			// mem set
			m_nodes.resize(m_mapSize.x);
			for (int x = stPosX; x < endPosX; ++x)
			{
				m_nodes[x + endPosX].resize(m_mapSize.y);
			}

			while (!in.eof())
			{
				in >> tx >> ty;
				in >> sx >> sy;
				in >> p;
				m_nodes[tx][ty] = new PassabilityNode(Vector2((tx + stPosX) * sx, (ty + stPosY) * sy),
					Vector2(sx, sy), static_cast<AreaTypes>(p));
				
				m_nodes[tx][ty]->UpdateRect();
			}

			m_nodeSize = m_nodes[0][0]->GetSize();

			in.close();

			return true;
		}
	}
	return false;
}

void PassabilityMap::SetMap(const string& src)
{
	m_resource = ResourceManager::instance()->GetResource(src);

	if (m_resource)
	{
		if (LoadMap())
		{
			return;
		}
	}
	throw std::exception("Can't load passability resource");
}

Vector2 PassabilityMap::WorldToNodeIndex(const Vector2& pos)
{
	int x = pos.x / m_nodeSize.x + m_indexOffset.x;
	int y = pos.y / m_nodeSize.y + m_indexOffset.y;
	return Vector2(x, y);
}

Vector2 PassabilityMap::NodeIndexToWorld(const Vector2& pos)
{
	auto nd = m_nodes[pos.x][pos.y];
	return nd->GetPos() + (nd->GetSize() / 2);
}

void PassabilityMap::FillPMap(vector<vector<int>>& pMap)
{
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		for (int y = 0; y < m_mapSize.y; ++y)
		{
			// pMap[x][y] = m_nodes[x][y]->m_type == 0 ? 0 : 1;
			// pMap[x][y] = m_nodes[x][y]->GetType() == PASSIBLE_AREA ? 0 : 1;
			if (m_nodes[x][y]->GetType() == IMPASSIBLE_AREA)
			{
				pMap[x][y] = 1;
			}
			else
			{
				pMap[x][y] = 0;
			}
		}
	}
}

bool PassabilityMap::IsAreaPossible(PassabilityArea * area)
{
	vector<Vector2> nodePoses;
	auto worldPoses = area->GetWorldPoses();
	for (auto && worldPos : worldPoses)
	{
		nodePoses.emplace_back(WorldToNodeIndex(worldPos));
	}

	for (int i = 0; i < worldPoses.size(); ++i)
	{
		if (!(IsInMap(nodePoses[i]) && 
			m_nodes[nodePoses[i].x][nodePoses[i].y]->IsInside(worldPoses[i]) &&
			m_nodes[nodePoses[i].x][nodePoses[i].y]->GetType() != IMPASSIBLE_AREA))
		{
			return false;
		}
	}
	return true;
}

PassabilityMap::AreaTypes PassabilityMap::GetAreaTypeInPos(const Vector2& pos)
{
	auto node = WorldToNodeIndex(pos);
	return m_nodes[node.x][node.y]->GetType();
}

void PassabilityMap::Update()
{
	if (KeyboardInput::instance()->GetState() == kb::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == kb::O)
		{
			if (m_editMode)
			{
				SaveMap();
			}
		}
		
		if (KeyboardInput::instance()->GetKey() == kb::L)
		{
			m_editMode = !m_editMode;
		}
	}
	
	if (m_editMode && MouseInput::instance()->GetState() == MouseInput::MOUSE_BUTTON_DOWN)
	{
		auto pos = MouseInput::instance()->GetPosInMap();

		int stPosX = -m_indexOffset.x, endPosX = m_indexOffset.x;
		int stPosY = -m_indexOffset.y, endPosY = m_indexOffset.y;

		for (int x = stPosX; x < endPosX; ++x)
		{
			for (int y = stPosY; y < endPosY; ++y)
			{
				if (m_nodes[x + endPosX][y + endPosY]->IsInside(pos))
				{
					if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_LEFT)
					{
						auto keys = KeyboardInput::instance()->GetKeyMap();
						if (keys.empty())
						{
							m_nodes[x + endPosX][y + endPosY]->SetType(IMPASSIBLE_AREA);
						}
						else
						{
							if (KeyboardInput::instance()->IsKeyPressed(Key1))
							{
								m_nodes[x + endPosX][y + endPosY]->SetType(TRIGGER_AREA);
							}
							else if (KeyboardInput::instance()->IsKeyPressed(Key2))
							{
								m_nodes[x + endPosX][y + endPosY]->SetType(LADDER_AREA);
							}
						}
					}
					else if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_RIGHT)
					{
						m_nodes[x + endPosX][y + endPosY]->SetType(PASSIBLE_AREA);
					}
				}
			}
		}
	}
}

void PassabilityMap::Render()
{
	if (m_editMode)
	{
		int stPosX = -m_indexOffset.x, endPosX = m_indexOffset.x;
		int stPosY = -m_indexOffset.y, endPosY = m_indexOffset.y;

		auto diff = Camera::instance()->GetDiff();
		for (int x = stPosX; x < endPosX; ++x)
		{
			for (int y = stPosY; y < endPosY; ++y)
			{
				SDL_SetRenderDrawColor(m_renderer, 0, 250, 0, 100);
				PassabilityNode * nd = m_nodes[x + endPosX][y + endPosY];
				SDL_Rect localRect = nd->GetRenderRect();
				
				// Apply zoom
				localRect.x *= Camera::instance()->GetZoom();
				localRect.y *= Camera::instance()->GetZoom();
				localRect.w *= Camera::instance()->GetZoom();
				localRect.h *= Camera::instance()->GetZoom();

				localRect.x = localRect.x + diff.x;
				localRect.y = localRect.y + diff.y;
				
				SDL_RenderDrawRect(m_renderer, &localRect);

				if (nd->GetType() != PASSIBLE_AREA)
				{
					switch (nd->GetType())
					{
					case IMPASSIBLE_AREA: break;
					case TRIGGER_AREA:
						SDL_SetRenderDrawColor(m_renderer, 205, 24, 255, 100);
						break;
					case LADDER_AREA:
						SDL_SetRenderDrawColor(m_renderer, 24, 121, 221, 230);
						break;
					}
					SDL_RenderFillRect(m_renderer, &localRect);
				}
			}
		}

		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	}
}

bool PassabilityMap::IsInMap(const Vector2& pos)
{
	return pos.x >= 0 && pos.x < m_mapSize.x
		&& pos.y >= 0 && pos.y <= m_mapSize.y;
}

void SDL_DrawCircle(SDL_Renderer* renderer, const Vector2& centre, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	SDL_SetRenderDrawColor(renderer, 250, 0, 0, 255);
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, (int)centre.x + x, (int)centre.y - y);
		SDL_RenderDrawPoint(renderer, (int)centre.x + x, (int)centre.y + y);
		SDL_RenderDrawPoint(renderer, (int)centre.x - x, (int)centre.y - y);
		SDL_RenderDrawPoint(renderer, (int)centre.x - x, (int)centre.y + y);
		SDL_RenderDrawPoint(renderer, (int)centre.x + y, (int)centre.y - x);
		SDL_RenderDrawPoint(renderer, (int)centre.x + y, (int)centre.y + x);
		SDL_RenderDrawPoint(renderer, (int)centre.x - y, (int)centre.y - x);
		SDL_RenderDrawPoint(renderer, (int)centre.x - y, (int)centre.y + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
