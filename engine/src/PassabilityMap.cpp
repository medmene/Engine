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
	int stPosX = -((int)m_mapSize.x / 2), endPosX = ((int)m_mapSize.x / 2);
	int stPosY = -((int)m_mapSize.y / 2), endPosY = ((int)m_mapSize.x / 2);
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

void PassabilityMap::Init(SDL_Renderer * renderer, const string & src, ResourceManager::Type type)
{
	m_renderer = renderer;
	m_resource = ResourceManager::instance()->GetResource(src, type);

	if (m_resource)
	{
		std::ifstream in;
		in.open(m_resource->GetPath());
		
		if (in.is_open())
		{
			float tx = 0, ty = 0, sx = 0, sy = 0, p = 0;
			in >> tx >> ty; // map size
		
			m_mapSize = Vector2(tx, ty);
			
			int stPosX = -((int)m_mapSize.x / 2), endPosX = ((int)m_mapSize.x / 2);
			int stPosY = -((int)m_mapSize.y / 2);
		
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
					Vector2(sx,sy), true);
		
				in >> p;
				m_nodes[tx][ty]->m_passible = p == 1 ? true : false;
				m_nodes[tx][ty]->UpdateRect();
			}
		
			in.close();
		}
		
		return;
	}
	throw std::exception("Can't load passability resource");
}

void PassabilityMap::SaveMap()
{
	if (m_resource)
	{
		std::ofstream out;
		out.open(m_resource->GetPath());
		
		if (out.is_open())
		{
			out << m_mapSize.x << " " << m_mapSize.y << "\n";
			
			int stPosX = -((int)m_mapSize.x / 2), endPosX = ((int)m_mapSize.x / 2);
			int stPosY = -((int)m_mapSize.y / 2), endPosY = ((int)m_mapSize.x / 2);
			
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
		}
		
		out.close();
	}
}

bool PassabilityMap::IsAreaPossible(PassabilityArea * area)
{
	//				higher
	//				*
	//			*		*
	//	  left *	*	 * right
	//			*		*
	//				*
	//				lower
	//
	//

	// auto checkInMap = [this](int x, int y)
	// {
	// 	return x >= 0 && x < m_mapSize.x
	// 		&& y >= 0 && y <= m_mapSize.y;
	// };
	//
	// auto size = m_nodes[0][0]->m_size;
	// int indXLeft = (int)((area->m_pos.x - area->m_radius) / size.x) + m_mapSize.x / 2;
	// int indYLeft = (int)(area->m_pos.y / size.y) + m_mapSize.y / 2;
	//
	// if (!checkInMap(indXLeft, indYLeft) || !checkInMap(indXLeft + 1, indYLeft + 1))
	// {
	// 	return false;
	// }
	//
	// m_nodes[indXLeft][indYLeft];


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
		auto pos = MouseInput::instance()->GetPos();
		pos = pos + Camera::instance()->GetPos() - Camera::instance()->GetPosInWnd();


		int stPosX = -((int)m_mapSize.x / 2), endPosX = ((int)m_mapSize.x / 2);
		int stPosY = -((int)m_mapSize.y / 2), endPosY = ((int)m_mapSize.x / 2);

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
		int stPosX = -((int)m_mapSize.x / 2), endPosX = ((int)m_mapSize.x / 2);
		int stPosY = -((int)m_mapSize.y / 2), endPosY = ((int)m_mapSize.x / 2);
		
		for (int x = stPosX; x < endPosX; ++x)
		{
			for (int y = stPosY; y < endPosY; ++y)
			{
				PassabilityNode * nd = m_nodes[x + endPosX][y + endPosY];
				SDL_Rect localRect = nd->m_rect;

				localRect.x = localRect.x + Camera::instance()->GetDiff().x;
				localRect.y = localRect.y + Camera::instance()->GetDiff().y;

				SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
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

void SDL_DrawCircle(SDL_Renderer* renderer, const Vector2& centre, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
