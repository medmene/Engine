#include "include/GameModeChangeController.h"


GameModeChangeController * GameModeChangeController::sm_instance = nullptr;

GameModeChangeController::GameModeChangeController()
	: m_curState(HIDDEN)
	, m_windowSize(Vector2::uno)
{
}

GameModeChangeController* GameModeChangeController::instance()
{
	if (!sm_instance)
	{
		sm_instance = new GameModeChangeController();
	}
	return sm_instance;
}

void GameModeChangeController::Init(SDL_Renderer* r, const Vector2& wSize)
{
	m_renderer = r;
	m_windowSize = wSize;
}

void GameModeChangeController::StartHiding()
{
	m_counter = 0.f;
	m_curState = HIDING;
}

void GameModeChangeController::StartShowing()
{
	m_counter = 0.f;
	m_curState = SHOWING;
}

void GameModeChangeController::Update(float dt)
{
	if (m_loadingTime > 0)
	{
		m_loadingTime -= dt;
		if (m_loadingTime <= 0)
		{
			StartShowing();
		}
		return; 
	}
	
	if (m_curState == HIDING)
	{
		m_counter += dt;
		if (m_counter > m_fadeTime)
		{
			m_curState = HIDDEN;
			m_counter = 0.f;
		}
	}
	
	if (m_curState == SHOWING)
	{
		m_counter += dt;
		if (m_counter > m_fadeTime)
		{
			m_curState = SHOWN;
			m_counter = 0.f;
		}
	}
}

void GameModeChangeController::Render()
{
	if (m_loadingTime > 0 || m_curState == HIDDEN)
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_Rect rct = { 0, 0, (int)m_windowSize.x, (int)m_windowSize.y };
		SDL_RenderFillRect(m_renderer, &rct);
	}
	
	if (m_curState == HIDING)
	{
		float progress = m_counter / m_fadeTime;
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, (int)255 * progress);
		SDL_Rect rct = { 0, 0, (int)m_windowSize.x, (int)m_windowSize.y };
		SDL_RenderFillRect(m_renderer, &rct);
	}
	else if (m_curState == SHOWING)
	{
		float progress = 1 - m_counter / m_fadeTime;
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255 * progress);
		SDL_Rect rct = { 0, 0, (int)m_windowSize.x, (int)m_windowSize.y };
		SDL_RenderFillRect(m_renderer, &rct);
	}
	else
	{
		return;
	}
}

