#include "include/PassabilityMap.h"
#include <fstream>
#include "include/Camera.h"
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"


PassabilityMap * PassabilityMap::sm_instance = new PassabilityMap();

PassabilityNode::PassabilityNode(const Vector2& pos, const Vector2& size, bool passible)
	: m_pos(pos)
	, m_size(size)
	, m_passible(passible)
{
	UpdateRect();
}

bool PassabilityNode::IsInside(const Vector2& pos)
{
	return pos.x >= m_pos.x && pos.x <= m_pos.x + m_size.x
		&& pos.y >= m_pos.y && pos.y <= m_pos.y + m_size.y;
}

void PassabilityNode::UpdateRect()
{
	m_rect = { (int)m_pos.x, (int)m_pos.y, (int)m_size.x, (int)m_size.y };
}

// --------------------------------------------------------------------------------------------- //

PassabilityArea::PassabilityArea()
	: m_pos(Vector2::zero)
	, m_radius(0.f)
{
}

PassabilityArea::PassabilityArea(const Vector2& pos, float rad)
	: m_pos(pos)
	, m_radius(rad)
{
}

// --------------------------------------------------------------------------------------------- //

PassabilityMap::PassabilityMap()
	: m_mapSize(Vector2(200, 200))
	, m_nodeSize(Vector2(30, 25))
	, m_indexOffset(Vector2((int)m_mapSize.x / 2, (int)m_mapSize.y / 2))
{
	// m_nodes.resize(200);
	// Vector2 size(30, 25);
	//
	// int stPosX = -((int)m_mapSize.x / 2), endPosX = ((int)m_mapSize.x / 2);
	// int stPosY = -((int)m_mapSize.y / 2), endPosY = ((int)m_mapSize.x / 2);
	//
	// for (int x = stPosX; x < endPosX; ++x)
	// {
	// 	m_nodes[x + endPosX].resize(m_mapSize.y);
	// 	
	// 	for (int y = stPosY; y < endPosY; ++y)
	// 	{
	// 		m_nodes[x + endPosX][y + endPosY] = new PassabilityNode(Vector2(x * size.x, y * size.y), size, true);
	// 	}
	// }
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
					out << nd->m_size.x << " " << nd->m_size.y << " ";
					out << (nd->m_passible ? 1 : 0);
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
			float tx = 0, ty = 0, sx = 0, sy = 0, p = 0;
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
				m_nodes[tx][ty] = new PassabilityNode(Vector2((tx + stPosX) * sx, (ty + stPosY) * sy),
					Vector2(sx, sy), true);

				in >> p;
				m_nodes[tx][ty]->m_passible = p == 1 ? true : false;
				m_nodes[tx][ty]->UpdateRect();
			}

			m_nodeSize = Vector2(m_nodes[0][0]->m_size.x, m_nodes[0][0]->m_size.y);

			in.close();

			return true;
		}
	}
	return false;
}

void PassabilityMap::SetMap(const string& src, ResourceManager::Type type)
{
	m_resource = ResourceManager::instance()->GetResource(src, type);

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
	return Vector2(nd->m_pos.x + nd->m_size.x / 2,
		nd->m_pos.y + nd->m_size.y / 2);
}

bool PassabilityMap::IsAreaPossible(PassabilityArea * area)
{
	//				higher
	//		   *	*	 *
	//			*		*
	//	  left *	*	 * right
	//			*		*
	//		   *	*	 *
	//				lower
	//
	//

	const int cornerOffset = (int)sqrt(area->m_radius*area->m_radius / 2);
	
	Vector2 posLeft = area->m_pos; posLeft.x -= area->m_radius;
	Vector2 posTopLeft = area->m_pos; posTopLeft.x -= cornerOffset; posTopLeft.y -= cornerOffset;
	Vector2 posTop = area->m_pos; posTop.y -= area->m_radius;
	Vector2 posTopRight = area->m_pos; posTopRight.x += cornerOffset; posTopRight.y -= cornerOffset;
	Vector2 posRight = area->m_pos; posRight.x += area->m_radius;
	Vector2 posBottomRight = area->m_pos; posBottomRight.x += cornerOffset; posBottomRight.y += cornerOffset;
	Vector2 posBottom = area->m_pos; posBottom.y += area->m_radius;
	Vector2 posBottomLeft = area->m_pos; posBottomLeft.x -= cornerOffset; posBottomLeft.y += cornerOffset;
	
	int xLeft = (int)((area->m_pos.x - area->m_radius) / m_nodeSize.x) + m_indexOffset.x;
	int yLeft = (int)(area->m_pos.y / m_nodeSize.y) + m_indexOffset.y;

	int xTopLeft = (int)((area->m_pos.x - cornerOffset) / m_nodeSize.x) + m_indexOffset.x;
	int yTopLeft = (int)((area->m_pos.y - cornerOffset) / m_nodeSize.y) + m_indexOffset.y;
	
	int xTop = (int)(area->m_pos.x / m_nodeSize.x) + m_indexOffset.x;
	int yTop = (int)((area->m_pos.y - area->m_radius) / m_nodeSize.y) + m_indexOffset.y;

	int xTopRight = (int)((area->m_pos.x + cornerOffset) / m_nodeSize.x) + m_indexOffset.x;
	int yTopRight = (int)((area->m_pos.y - cornerOffset) / m_nodeSize.y) + m_indexOffset.y;

	int xRight = (int)((area->m_pos.x + area->m_radius) / m_nodeSize.x) + m_indexOffset.x;
	int yRight = (int)(area->m_pos.y / m_nodeSize.y) + m_indexOffset.y;

	int xBottomRight = (int)((area->m_pos.x + cornerOffset) / m_nodeSize.x) + m_indexOffset.x;
	int yBottomRight = (int)((area->m_pos.y + cornerOffset) / m_nodeSize.y) + m_indexOffset.y;
	
	int xBottom = (int)(area->m_pos.x / m_nodeSize.x) + m_indexOffset.x;
	int yBottom = (int)((area->m_pos.y + area->m_radius) / m_nodeSize.y) + m_indexOffset.y;

	int xBottomLeft = (int)((area->m_pos.x - cornerOffset) / m_nodeSize.x) + m_indexOffset.x;
	int yBottomLeft = (int)((area->m_pos.y + cornerOffset) / m_nodeSize.y) + m_indexOffset.y;
	
	if (!IsInMap(xLeft, yLeft) || !IsInMap(xTop, yTop) ||
		!IsInMap(xTopLeft, yTopLeft) || !IsInMap(xTopRight, yTopRight) ||
		!IsInMap(xBottomRight, yBottomRight) || !IsInMap(xBottomLeft, yBottomLeft) ||
		!IsInMap(xRight, yRight) || !IsInMap(xBottom, yBottom))
	{
		return false;
	}

	PassabilityNode * ndLeft =			m_nodes[xLeft][yLeft];
	PassabilityNode * ndTopLeft =		m_nodes[xTopLeft][yTopLeft];
	PassabilityNode * ndTop =			m_nodes[xTop][yTop];
	PassabilityNode * ndTopRight =		m_nodes[xTopRight][yTopRight];
	PassabilityNode * ndRight =			m_nodes[xRight][yRight];
	PassabilityNode * ndBottomRight =	m_nodes[xBottomRight][yBottomRight];
	PassabilityNode * ndBottom =		m_nodes[xBottom][yBottom];
	PassabilityNode * ndBottomLeft =	m_nodes[xBottomLeft][yBottomLeft];
	
	if (ndLeft->IsInside(posLeft) &&
		ndTop->IsInside(posTop) &&
		ndTopLeft->IsInside(posTopLeft) &&
		ndTopRight->IsInside(posTopRight) &&
		ndBottomRight->IsInside(posBottomRight) &&
		ndBottomLeft->IsInside(posBottomLeft) &&
		ndRight->IsInside(posRight) &&
		ndBottom->IsInside(posBottom))
	{
		if (ndLeft->m_passible &&
			ndTop->m_passible &&
			ndRight->m_passible &&
			ndTopLeft->m_passible &&
			ndTopRight->m_passible &&
			ndBottomRight->m_passible &&
			ndBottomLeft->m_passible &&
			ndBottom->m_passible)
		{
			return true;
		}
	}

	return false;
}

void PassabilityMap::Update()
{
	if (KeyboardInput::instance()->GetState() == KeyboardInput::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == KeyboardInput::O)
		{
			if (m_editMode)
			{
				SaveMap();
			}
		}
		
		if (KeyboardInput::instance()->GetKey() == KeyboardInput::L)
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
						m_nodes[x + endPosX][y + endPosY]->m_passible = false;
					}
					else if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_RIGHT)
					{
						m_nodes[x + endPosX][y + endPosY]->m_passible = true;
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
		
		for (int x = stPosX; x < endPosX; ++x)
		{
			for (int y = stPosY; y < endPosY; ++y)
			{
				PassabilityNode * nd = m_nodes[x + endPosX][y + endPosY];
				SDL_Rect localRect = nd->m_rect;

				auto diff = Camera::instance()->GetDiff();
				localRect.x = localRect.x + diff.x;
				localRect.y = localRect.y + diff.y;
				
				SDL_SetRenderDrawColor(m_renderer, 0, 250, 0, 100);
				SDL_RenderDrawRect(m_renderer, &localRect);

				if (!nd->m_passible)
				{
					SDL_RenderFillRect(m_renderer, &localRect);
				}
			}
		}
	}
}

bool inline PassabilityMap::IsInMap(int x, int y)
{
	return x >= 0 && x < m_mapSize.x
		&& y >= 0 && y <= m_mapSize.y;
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
