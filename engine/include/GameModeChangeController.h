#pragma once

#include "Core.h"
#include "Vector2.h"


class GameModeChangeController
{
	enum State
	{
		HIDDEN,
		HIDING,
		SHOWN,
		SHOWING,
		LOADING
	};
public:
	static GameModeChangeController * instance();

	void Init(SDL_Renderer * r, const Vector2& wSize);

	bool IsHiding() { return m_curState == HIDING; }
	bool IsHidden() { return m_curState == HIDDEN; }
	bool IsShown() { return m_curState == SHOWN; }

	void StartHiding();
	void StartShowing();
	
	void Update(float dt);
	void Render();
private:
	SDL_Renderer				  * m_renderer = nullptr;
	State							m_curState;
	Vector2							m_windowSize;
	float							m_loadingTime = 3000.f;
	float							m_fadeTime = 1000.f;
	float							m_counter = 0.f;

	GameModeChangeController();
	GameModeChangeController(const GameModeChangeController&) = default;
	static GameModeChangeController			  * sm_instance;
};
