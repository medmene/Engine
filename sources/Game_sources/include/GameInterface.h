#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/Window.h"

class GameObject;

class GameInterface : public Window
{
public:
	GameInterface(shared_ptr<WindowManager> w, SDL_Renderer * r, const Vector2 & wSize);
	
	void Run() override;
	void Disappear() override;

	static string GetName() { return "game_interface"; }
	
	string GetWindowName() override { return GetName(); }
	
	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible);
	
	void Update(float dt) override;
	void Render() override;
private:
	bool								m_visible;
	vector<shared_ptr<GameObject>>		m_elements;
};