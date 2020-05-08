#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/Window.h"


class GameObject;
class NPC;

class LevelBase : public Window
{
public:
	LevelBase(shared_ptr<WindowManager> wm, SDL_Renderer *r, const Vector2 & winSize);

	void Run() override;
	void Disappear() override;
	void Update(float dt) override;
	void Render() override;
	
protected:
	vector<GameObject*>			m_objects;
	vector<NPC*> 				m_npcs;
	bool						m_loadingFinished = false;
};