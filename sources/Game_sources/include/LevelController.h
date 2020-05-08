#pragma once
#include "LevelBase.h"
#include "include/Core.h"

class LevelController
{
	enum ChangingState
	{
		HIDDEN,
		HIDING,
		SHOWN,
		SHOWING
	};
	LevelController();
public:
	enum LevelState
	{
		MENU = 0,
		LEVEL1,
		LEVEL2,
		LEVEL3,
		LEVEL4,
		LEVEL5,
		UNDEFINED,
		SIZE
	};
	
	static LevelController * instance();

	void Init(SDL_Renderer *r, const Vector2 & wSize);
	
	void ChangeState(LevelState newState);
	void RunStartState();

	void Update(float dt);
	void Render();
private:
	SDL_Renderer				  * m_renderer = nullptr;
	Vector2							m_windowSize;
	
	vector<LevelBase *>				m_levels;
	int								m_skipFrame;
	LevelState						m_currentState;
	LevelState						m_prevState;
	
	static LevelController		  * sm_instance;
};