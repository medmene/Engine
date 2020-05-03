#pragma once
#include "include/Core.h"

class GameObject;

class GameInterface
{
public:
	
	GameInterface(SDL_Renderer * r);
	~GameInterface();
	void Init();
	
	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible);
	
	void Update(float dt);
	void Render();
private:
	SDL_Renderer					  * m_renderer;
	bool								m_visible;
	vector<shared_ptr<GameObject>>		m_elements;
};