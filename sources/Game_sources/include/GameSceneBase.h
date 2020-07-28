#pragma once
#include "include/Core.h"
#include "include/window/Window.h"


class GameObject;
class NPC;

class GameSceneBase : public Window
{
public:
	GameSceneBase(shared_ptr<WindowManager> wm);

	void LoadScene() override;
	void Run() override;
	void Disappear() override;
	void Update(float dt) override;
	void Render() override;
	
	GameObject* GetGameObject(const string & name);
	GameObject* GetGoundObject(const string & name);

	void AddObject(GameObject * obj);

protected:

	vector<GameObject*>			m_groundObjects;
	vector<GameObject*>			m_objects;

	bool						m_useSort;
	string						m_sceneName;
	
	static bool SortComparer(const GameObject* lhs, const GameObject* rhs);
};