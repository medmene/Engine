#pragma once
#include "include/Core.h"
#include "include/Vector2.h"

class GameObject;

class GameInterface
{
public:
	
	GameInterface(SDL_Renderer * r, const Vector2 & wSize);
	~GameInterface();
	void Init();
	
	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible);
	
	void Update(float dt);
	void Render();
private:
	Vector2								m_windowSize;
	SDL_Renderer					  * m_renderer;
	bool								m_visible;
	vector<shared_ptr<GameObject>>		m_elements;
};