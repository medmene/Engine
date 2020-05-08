#include "include/GameModeChangeController.h"
#include "include/KeyboardInput.h"
#include "include/MouseInput.h"
#include "Game_sources/include/GameWindow.h"
#include "Game_sources/include/LevelBase.h"


GameModeChangeController * GameModeChangeController::sm_instance = nullptr;

GameModeChangeController::GameModeChangeController()
	: m_curState(HIDDEN)
	, m_windowSize(Vector2::uno)
{
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
	MouseInput::instance()->LockInput();
	KeyboardInput::instance()->LockInput();
}

void GameModeChangeController::StartShowing()
{
	m_counter = 0.f;
	m_curState = SHOWING;
	MouseInput::instance()->LockInput();
	KeyboardInput::instance()->LockInput();
}

void GameModeChangeController::Update(float dt)
{
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
			MouseInput::instance()->UnlockInput();
			KeyboardInput::instance()->UnlockInput();
			m_curState = SHOWN;
			m_counter = 0.f;
		}
	}
}

void GameModeChangeController::Render()
{
	if (m_curState == HIDDEN)
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
}

