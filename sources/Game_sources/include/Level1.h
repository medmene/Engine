#pragma once
#include "include/Core.h"
#include "include/Vector2.h"


class GameObject;

struct Level1
{
	Level1(){}
	~Level1();

	void Init(SDL_Renderer * renderer, const Vector2 & winSize);
	void Update(float dt);
	void Draw();

//---------------------------------------------------------------//

	vector<GameObject*>			m_backgrounds;
	vector<GameObject*>			m_grounds;
	vector<GameObject*>			m_objects;

	Vector2						m_winSize;
	SDL_Renderer			  * m_renderer;
};