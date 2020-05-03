#pragma once
#include "Core.h"
#include "Character.h"
#include "Vector2.h"

class MovingController;

class BehaviourController
{
	enum State
	{
		WAIT = 0,
		MOVE,
		TALK,
		BATTLE,
		UNDEFINED
	};
public:
	BehaviourController(SDL_Renderer *r , ICharacter * owner);
	~BehaviourController();

	auto GetMovingController() { return m_movingController; }

	bool IsRunning() { return m_running; }
	
	void SetAnchorPoint(const Vector2 point) { m_anchorPoint = point; }
	void SetNormalSpeed(float speed) { m_normalSpeed = speed; }
	void SetRunSpeed(float speed) { m_runSpeed = speed; }
	
	Vector2 GetAnchorPoint() { return m_anchorPoint; }
	float GetNormalSpeed() { return m_normalSpeed; }
	float GetRunSpeed() { return m_runSpeed; }
	
	void Update(float dt);
	void Render();
private:
	SDL_Renderer			  *	m_renderer = nullptr;
	ICharacter				  * m_owner = nullptr;
	MovingController		  * m_movingController = nullptr;
	Vector2						m_anchorPoint;
	Vector2						m_anchorArea;
	
	State						m_currentState;
	float						m_waitingTime = 0.f;
	bool						m_running;
	int							m_movingRadius;
	float						m_normalSpeed;
	float						m_runSpeed;

	bool						m_visualisation = false;

	void ChangeState(State newState, bool force = false);
	void OnStateWaitEntering();
	void OnStateMoveEntering();
	void OnStateTalkEntering();
	void OnStateBattleEntering();
};