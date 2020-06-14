#pragma once
#include "GameSceneBase.h"

class GameObject;

class GameInterface : public GameSceneBase
{
public:
	GameInterface(shared_ptr<WindowManager> w);
	
	void Run() override;
	void LoadScene() override;
	
	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible);
private:
	bool								m_visible;
};