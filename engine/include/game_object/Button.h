#pragma once
#include "include/game_object/Label.h"
#include "include/game_object/GameObject.h"

class Animator;

class Button : public GameObject
{
	explicit Button();
public:
	Button(const string & name);
	~Button();
	void LoadGraphics(pugi::xml_node * node) override;

	void SetOnclick(function<bool()> onClick) { m_onClick = onClick; }

	void Update(float dt) override;
	void Render() override;
	
private:
	bool						m_isPressed = false;
	bool						m_isTextVisible = false;
	function<bool()>			m_onClick;
	Label					  * m_label = nullptr;
	
	bool IsMouseInside();
};