#include "include/MovingController.h"
#include "include/PathFinder.h"
#include "include/Character.h"
#include "include/GameObject.h"
#include "include/KeyboardInput.h"
#include "include/Camera.h"
#include "include/Animator.h"


MovingController::MovingController()
	: m_speedModifier(0.16f)
	, m_curSpeed(Vector2::zero)
	, m_searching(false)
	, m_moving(false)
	, m_hasPath(false)
	, m_pathIndex(0)
	, m_lastDir(0)
	, m_visualisation(false)
{
}

MovingController::MovingController(SDL_Renderer *r, ICharacter * owner, float speedMod)
	: m_speedModifier(speedMod)
	, m_curSpeed(Vector2::zero)
	, m_searching(false)
	, m_moving(false)
	, m_hasPath(false)
	, m_pathIndex(0)
	, m_owner(owner)
	, m_visualisation(false)
{
	m_renderer = r;

	m_ownerObj = dynamic_cast<GameObject *>(owner);
	
	m_dirs[0][0] = 1;
	m_dirs[0][1] = 0;
	m_dirs[0][2] = 7;
	m_dirs[1][0] = 2;
	m_dirs[1][2] = 6;
	m_dirs[2][0] = 3;
	m_dirs[2][1] = 4;
	m_dirs[2][2] = 5;
	
	m_finder = new PathFinder();
}

MovingController::~MovingController()
{
	delete m_finder;
}

void MovingController::MoveToPos(const Vector2 &pos)
{
	if (m_finder && m_owner && !IsMoving())
	{
		m_searching = true;
		m_finder->StartFinding(m_ownerObj->GetCenterPos(), pos);
	}
}

void MovingController::Update(float dt)
{
	if (KeyboardInput::instance()->GetState() == kb::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == kb::I)
		{
			m_visualisation = !m_visualisation;
		}
	}
	
	if (m_searching)
	{
		if (!m_finder->InProgress())
		{
			m_movingPath.clear();
			m_finder->GetResult(m_movingPath);

			if (!m_movingPath.empty())
			{
				m_moving = true;
				m_pathIndex = 0;
			}
			m_hasPath = !m_movingPath.empty();
			m_searching = false;
		}
	}

	if (m_moving)
	{
		if (m_ownerObj)
		{
			auto oldPos = m_ownerObj->GetCenterPos();
			auto dir = m_movingPath[m_pathIndex] - oldPos;
			float dirLen = dir.length();

			int signX = (dir.x > 0) - (dir.x < 0) + 1; // 0 1 2
			int signY = (dir.y > 0) - (dir.y < 0) + 1; // 0 1 2

			m_lastDir = m_dirs[signX][signY];
			string animName = m_directionsOfAnimations[m_lastDir];
			if (!m_ownerObj->GetAnimator()->IsAnimationPlaying(animName))
			{
				m_ownerObj->GetAnimator()->PlayAnimation(animName);
			}
			
			float coef = m_speedModifier / dirLen;

			dir *= coef;

			auto newPos = oldPos + dir;
			m_ownerObj->UpdateCenterPos(newPos);

			if (dirLen < m_speedModifier)
			{
				m_pathIndex++;
				if (m_pathIndex == m_movingPath.size())
				{
					m_movingPath.clear();
					m_moving = false;
				}
			}
		}
	}
}

void MovingController::Render()
{
	if (m_visualisation)
	{
		if (!m_movingPath.empty())
		{
			auto diff = Camera::instance()->GetDiff();

			SDL_SetRenderDrawColor(m_renderer, 250, 0, 0, 100);
			SDL_Rect rct = { (int)m_movingPath[0].x - 7, (int)m_movingPath[0].y - 7 , 15, 15 };
			rct.x *= Camera::instance()->GetZoom();
			rct.y *= Camera::instance()->GetZoom();
			rct.w *= Camera::instance()->GetZoom();
			rct.h *= Camera::instance()->GetZoom();
			rct.x = rct.x + diff.x;
			rct.y = rct.y + diff.y;
			SDL_RenderFillRect(m_renderer, &rct);

			SDL_SetRenderDrawColor(m_renderer, 0, 0, 250, 100);
			for (int i = 1; i < m_movingPath.size(); ++i)
			{
				rct = { (int)m_movingPath[i].x - 5, (int)m_movingPath[i].y -5 , 10, 10};

				rct.x *= Camera::instance()->GetZoom();
				rct.y *= Camera::instance()->GetZoom();
				rct.w *= Camera::instance()->GetZoom();
				rct.h *= Camera::instance()->GetZoom();
				rct.x = rct.x + diff.x;
				rct.y = rct.y + diff.y;
				
				SDL_RenderFillRect(m_renderer, &rct);
			}
			
			SDL_SetRenderDrawColor(m_renderer, 250, 0, 0, 100);
			rct = { (int)m_movingPath[m_movingPath.size() - 1].x - 7, (int)m_movingPath[m_movingPath.size() - 1].y - 7 , 15, 15 };

			rct.x *= Camera::instance()->GetZoom();
			rct.y *= Camera::instance()->GetZoom();
			rct.w *= Camera::instance()->GetZoom();
			rct.h *= Camera::instance()->GetZoom();
			rct.x = rct.x + diff.x;
			rct.y = rct.y + diff.y;
			
			SDL_RenderFillRect(m_renderer, &rct);

			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
		}
	}
}