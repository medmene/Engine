#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "Label.h"
#include "GameObject.h"
#include "ResourceManager.h"

class Animator;

class Button : public GameObject
{
	explicit Button();
public:
	Button(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	
	void SetOnclick(function<void()> onClick) { m_onClick = onClick; }
	void SetLabel(const string& text, const string& src, ResourceManager::Type type);

	void Update(float dt) override;
	void Render() override;
	
private:
	bool						m_isPressed = false;
	function<void()>			m_onClick;
	Label					  * m_label = nullptr;
	
	bool IsMouseInside();
};