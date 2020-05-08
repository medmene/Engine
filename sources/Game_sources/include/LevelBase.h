#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/Window.h"


class GameObject;
class NPC;

class LevelBase : public Window
{
public:
	LevelBase(WindowManager * wm);
	~LevelBase();

	virtual void Init(SDL_Renderer * renderer, const Vector2 & winSize) = 0;
	void Update(float dt);
	void Render() override;

	//---------------------------------------------------------------//

	vector<GameObject*>			m_objects;
	vector<NPC*> 				m_npcs;

	Vector2						m_winSize;
	SDL_Renderer			  * m_renderer = nullptr;
	bool						m_loadingFinished = false;
};