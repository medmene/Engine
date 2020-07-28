#include "include/controller/MovingController.h"
#include "include/controller/PathFinder.h"
#include "include/game_object/npc/Character.h"
#include "include/game_object/GameObject.h"
#include "include/input/KeyboardInput.h"
#include "include/input/Camera.h"
#include "include/controller/Animator.h"
#include "include/controller/PassabilityMap.h"
#include "include/controller/BehaviourController.h"
#include "include/controller/other/DirectionSettings.h"


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

MovingController::MovingController(BehaviourController *ctrl, SDL_Renderer *r, ICharacter * owner, float speedMod)
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
	m_behaviour = ctrl;
	
	m_ownerObj = dynamic_cast<GameObject *>(owner);
	
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
			auto velocity = m_movingPath[m_pathIndex] - oldPos;
			float velocityLen = velocity.length();
			m_lastDir = DirectionSettings::VelocityToDirection(velocity);
			
			DirectionSettings::MovingState state = m_behaviour && m_behaviour->IsRunning()
				? DirectionSettings::RUNNING
				: DirectionSettings::GOING;
			string animName = DirectionSettings::GetDirectionAnimation(state, m_lastDir);
			
			if (!m_ownerObj->GetAnimator()->IsAnimationPlaying(animName))
			{
				m_ownerObj->GetAnimator()->PlayAnimation(animName);
			}

			velocity *= m_speedModifier / velocityLen;
			
			if (PassabilityMap::instance()->GetAreaTypeInPos(m_ownerObj->GetPivotPos()) == PassabilityMap::LADDER_AREA)
			{
				velocity *= LadderArea::GetMovingSpeedDebuff();
			}
			
			auto newPos = oldPos + velocity;
			m_ownerObj->UpdateCenterPos(newPos);

			if (velocityLen < m_speedModifier)
			{
				m_pathIndex++;
				if (m_pathIndex == m_movingPath.size())
				{
					// TODO add play idle animation here
					animName = DirectionSettings::GetDirectionAnimation(DirectionSettings::IDLE, m_lastDir);
					if (!m_ownerObj->GetAnimator()->IsAnimationPlaying(animName))
					{
						m_ownerObj->GetAnimator()->PlayAnimation(animName);
					}
					
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