#pragma once
#include "Core.h"
#include "Character.h"
#include "Vector2.h"



class MovingController;
class GameObject;

class BehaviourController
{
public:
	enum BehaviourState
	{
		WAIT = 0,
		MOVE,
		TALK,
		BATTLE,
		UNDEFINED
	};
	
	BehaviourController(SDL_Renderer *r , ICharacter * owner);
	~BehaviourController();

	auto GetMovingController() { return m_movingController; }

	bool IsRunning() { return m_running; }
	bool IsFreeBehaviour() { return m_freeBehaviour; }
	
	void SetAnchorPoint(const Vector2 & point) { m_anchorPoint = point; }
	void SetAnchorArea(const Vector2 & area) { m_anchorArea = area; }
	void SetNormalSpeed(float speed) { m_normalSpeed = speed; }
	void SetRunSpeed(float speed) { m_runSpeed = speed; }
	void SetFreeBehaviour(bool free) { m_freeBehaviour = free; }
	
	Vector2 GetAnchorPoint() const { return m_anchorPoint; }
	float GetNormalSpeed() { return m_normalSpeed; }
	float GetRunSpeed() { return m_runSpeed; }
	
	void Update(float dt);
	void Render();
private:
	SDL_Renderer				  *	m_renderer = nullptr;
	ICharacter					  * m_owner = nullptr;
	GameObject					  * m_ownerObj = nullptr;
	shared_ptr<MovingController>	m_movingController;
	Vector2							m_anchorPoint;
	Vector2							m_anchorArea;

	bool							m_freeBehaviour;
	BehaviourState					m_currentState;
	float							m_waitingTime = 0.f;
	bool							m_running;
	float							m_normalSpeed;
	float							m_runSpeed;

	bool							m_visualisation = false;

	void ChangeState(BehaviourState newState, bool force = false);
	void OnStateWaitEntering();
	void OnStateMoveEntering();
	void OnStateTalkEntering();
	void OnStateBattleEntering();
};