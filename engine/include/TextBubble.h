#pragma once
#include "Core.h"
#include "Vector2.h"
#include "GameObject.h"


class TextBubble : public GameObject
{
public:
	enum Side
	{
		LEFT = 0,
		RIGHT
	};
	
	TextBubble(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);

	void SetSide(Side s);
	Side GetSide() { return m_currentSide; }

	void Update(float dt) override;
	void Render() override;
private:
	Side						m_currentSide;
	Vector2						m_defaultRelPos;
};