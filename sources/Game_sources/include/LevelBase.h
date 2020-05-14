#pragma once
#include "include/Core.h"
#include "include/Window.h"


class GameObject;
class NPC;

class LevelBase : public Window
{
public:
	LevelBase(shared_ptr<WindowManager> wm);

	void Run() override;
	void Disappear() override;
	void Update(float dt) override;
	void Render() override;
	
protected:
	vector<GameObject*>			m_groundObjects;
	vector<GameObject*>			m_objects;

	bool						m_useSort;
	
	static bool SortComparer(const GameObject* lhs, const GameObject* rhs);
};