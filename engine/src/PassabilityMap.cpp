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

PassabilityMap::PassabilityMap()
{
}

PassabilityMap::~PassabilityMap()
{
	for (auto && node : m_nodes)
	{
		delete node;
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

		float t1 = 0, t2 = 0;
		
		while(!in.eof())
		{
			m_nodes.emplace_back(new PassabilityNode(Vector2::zero, Vector2::zero, true));
			
			in >> t1 >> t2;
			m_nodes.back()->m_size.x = t1;
			m_nodes.back()->m_size.y = t2;
			
			in >> t1 >> t2;
			m_nodes.back()->m_pos.x = t1;
			m_nodes.back()->m_pos.y = t2;
			
			in >> t1;
			m_nodes.back()->m_passible = t1 == 1 ? true : false;
			m_nodes.back()->UpdateRect();
		}

		in.close();
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
			for (auto && node : m_nodes)
			{
				out << node->m_size.x << " " << node->m_size.y << " ";
				out << node->m_pos.x << " " << node->m_pos.y << " ";
				out << (node->m_passible ? 1 : 0);
				out << "\n";
			}
		}
		
		out.close();
	}
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
		for (auto && node : m_nodes)
		{
			if (node->IsInside(pos))
			{
				if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_LEFT)
				{
					node->m_passible = false;
				}
				else if (MouseInput::instance()->GetButton() == MouseInput::MOUSE_RIGHT)
				{
					node->m_passible = true;
				}
			}
		}
	}
}

void PassabilityMap::Render()
{
	if (m_editMode)
	{
		for (auto && node : m_nodes)
		{
			SDL_Rect localRect = node->m_rect;

			localRect.x = localRect.x + Camera::instance()->GetDiff().x;
			localRect.y = localRect.y + Camera::instance()->GetDiff().y;

			SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(m_renderer, 0, 250, 0, 100);
			SDL_RenderDrawRect(m_renderer, &localRect);

			if (!node->m_passible)
			{
				SDL_RenderFillRect(m_renderer, &localRect);
			}
		}
	}
}
