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

			UpdateMapTexture();

			return true;
		}
	}
	return false;
}

void PassabilityMap::UpdateMapTexture()
{
	if (m_mapSurface) 
	{
		SDL_FreeSurface(m_mapSurface);
		m_mapSurface = nullptr;
	}

	if (m_mapTexture) 
	{
		SDL_DestroyTexture(m_mapTexture);
		m_mapTexture = nullptr;
	}

	Vector2 sfSize = Vector2(m_mapSize.x * m_nodeSize.x, m_mapSize.y * m_nodeSize.y);
	m_mapSurface = SDL_CreateRGBSurface(0, static_cast<int>(sfSize.x), static_cast<int>(sfSize.y), 32, 0, 0, 0, 0);
	SDL_SetSurfaceBlendMode(m_mapSurface, SDL_BlendMode::SDL_BLENDMODE_BLEND);

	if (m_mapSurface)
	{
		auto emptyNode = SDL_CreateRGBSurface(0, static_cast<int>(m_nodeSize.x), static_cast<int>(m_nodeSize.y), 32, 0, 0, 0, 0);
		auto ladderNode = SDL_CreateRGBSurface(0, static_cast<int>(m_nodeSize.x), static_cast<int>(m_nodeSize.y), 32, 0, 0, 0, 0);
		auto triggerNode = SDL_CreateRGBSurface(0, static_cast<int>(m_nodeSize.x), static_cast<int>(m_nodeSize.y), 32, 0, 0, 0, 0);
		auto notPassibleNode = SDL_CreateRGBSurface(0, static_cast<int>(m_nodeSize.x), static_cast<int>(m_nodeSize.y), 32, 0, 0, 0, 0);
		SDL_SetSurfaceBlendMode(emptyNode, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetSurfaceBlendMode(ladderNode, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetSurfaceBlendMode(triggerNode, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetSurfaceBlendMode(notPassibleNode, SDL_BlendMode::SDL_BLENDMODE_BLEND);

		if (emptyNode && ladderNode && notPassibleNode && triggerNode)
		{
			auto set_pixel = [](SDL_Surface *surface, int x, int y, Uint32 pixel)
			{
				int bpp = surface->format->BytesPerPixel;
				/* Here p is the address to the pixel we want to set */
				Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

				switch (bpp) {
				case 1:
					*p = pixel;
					break;

				case 2:
					*(Uint16 *)p = pixel;
					break;

				case 3:
					if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
						p[0] = (pixel >> 16) & 0xff;
						p[1] = (pixel >> 8) & 0xff;
						p[2] = pixel & 0xff;
					}
					else {
						p[0] = pixel & 0xff;
						p[1] = (pixel >> 8) & 0xff;
						p[2] = (pixel >> 16) & 0xff;
					}
					break;

				case 4:
					*(Uint32 *)p = pixel;
					break;
				}
			};

			// Fill node with pixels
			for (int x = 0; x < m_nodeSize.x; ++x)
			{
				for (int y = 0; y < m_nodeSize.y; ++y)
				{
					// background
					set_pixel(notPassibleNode, x, y, 0x00FA0064);
					set_pixel(ladderNode, x, y, 0x1879D3E6);
					set_pixel(triggerNode, x, y, 0xCD18FF64);

					// borders
					if (y == 0 || y == m_nodeSize.y - 1) 
					{
						set_pixel(emptyNode, x, y, 0x00FA0064);
						set_pixel(notPassibleNode, x, y, 0x00FA0064);
						set_pixel(ladderNode, x, y, 0x00FA0064);
						set_pixel(triggerNode, x, y, 0x00FA0064);
					}
					if (x == 0 || x == m_nodeSize.x - 1)
					{
						set_pixel(emptyNode, x, y, 0x00FA0064);
						set_pixel(notPassibleNode, x, y, 0x00FA0064);
						set_pixel(ladderNode, x, y, 0x00FA0064);
						set_pixel(triggerNode, x, y, 0x00FA0064);
					}
				}
			}

			// Fill map with nodes
			for (int x = 0; x < m_mapSize.x; ++x)
			{
				for (int y = 0; y < m_mapSize.y; ++y)
				{
					SDL_Rect destRect;
					destRect.w = m_nodeSize.x;
					destRect.h = m_nodeSize.y;
					destRect.x = m_nodes[x][y]->GetPos().x + m_indexOffset.x * m_nodeSize.x;
					destRect.y = m_nodes[x][y]->GetPos().y + m_indexOffset.y * m_nodeSize.y;
					switch (m_nodes[x][y]->GetType())
					{
					case PASSIBLE_AREA:
						SDL_BlitSurface(m_mapSurface, nullptr, emptyNode, &destRect);
						break;
					case IMPASSIBLE_AREA:
						SDL_BlitSurface(m_mapSurface, nullptr, notPassibleNode, &destRect);
						break;
					case TRIGGER_AREA:
						SDL_BlitSurface(m_mapSurface, nullptr, triggerNode, &destRect);
						break;
					case LADDER_AREA:
						SDL_BlitSurface(m_mapSurface, nullptr, ladderNode, &destRect);
						break;
					}
				}
			}

			m_mapTexture = SDL_CreateTextureFromSurface(m_renderer, m_mapSurface);
			SDL_SetTextureBlendMode(m_mapTexture, SDL_BLENDMODE_BLEND);

			SDL_FreeSurface(emptyNode);
			SDL_FreeSurface(ladderNode);
			SDL_FreeSurface(triggerNode);
			SDL_FreeSurface(notPassibleNode);
		}
	}
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
		ProcessMouse();
	}
}

void PassabilityMap::ProcessMouse()
{
	auto pos = WorldToNodeIndex(MouseInput::instance()->GetPosInMap());

	if (m_nodes[pos.x][pos.y]->IsInside(MouseInput::instance()->GetPosInMap()))
	{
		if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_LEFT)
		{
			auto keys = KeyboardInput::instance()->GetKeyMap();
			if (keys.empty())
			{
				m_nodes[pos.x][pos.y]->SetType(IMPASSIBLE_AREA);
				UpdateMapTexture();
			}
			else
			{
				if (KeyboardInput::instance()->IsKeyPressed(Key1))
				{
					m_nodes[pos.x][pos.y]->SetType(TRIGGER_AREA);
					UpdateMapTexture();
				}
				else if (KeyboardInput::instance()->IsKeyPressed(Key2))
				{
					m_nodes[pos.x][pos.y]->SetType(LADDER_AREA);
					UpdateMapTexture();
				}
			}
		}
		else if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_RIGHT)
		{
			m_nodes[pos.x][pos.y]->SetType(PASSIBLE_AREA);
			UpdateMapTexture();
		}
	}
}

void PassabilityMap::Render()
{
	if (m_editMode)
	{
		SDL_Rect localRect = m_mapSurface->clip_rect;
		localRect.x -= localRect.w / 2;
		localRect.y -= localRect.h / 2;

		auto diff = Camera::instance()->GetDiff();
		// Apply zoom
		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		localRect.x = localRect.x + diff.x;
		localRect.y = localRect.y + diff.y;

		SDL_RenderCopy(m_renderer, m_mapTexture, nullptr, &localRect);
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
