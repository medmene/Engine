#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "Label.h"
#include "GameObject.h"
#include "ResourceManager.h"

class Animator;
class GameObject;

class Button : public GameObject
{
	explicit Button();
public:
	~Button();
	Button(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	
	void Update(float dt) override;
	bool IsMouseInside();

	void Render() override;
	
private:
	bool						m_isPressed = false;
};