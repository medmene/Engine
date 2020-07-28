#pragma once
#include "include/game_object/Label.h"
#include "include/game_object/GameObject.h"

class Animator;

class CheckBox : public GameObject
{
	explicit CheckBox();
public:
	CheckBox(const string & name);
	~CheckBox();
	void LoadGraphics(pugi::xml_node * node) override;

	void SetOnclick(function<bool()> onClick) { m_onClick = onClick; }
	void SetText(const u16string& text);

	void Update(float dt) override;
	void Render() override;
	
private:
	bool						m_checked = false;
	function<bool()>			m_onClick;
	Label					  * m_label = nullptr;
	
	bool IsMouseInside();
};