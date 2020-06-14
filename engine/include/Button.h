#pragma once
#include "Core.h"
#include "Label.h"
#include "GameObject.h"
#include "ResourceManager.h"

class Animator;

class Button : public GameObject
{
	explicit Button();
public:
	Button(const string & name);
	~Button();
	void LoadGraphics(pugi::xml_node * node) override;

	void SetOnclick(function<bool()> onClick) { m_onClick = onClick; }
	void SetLabel(const u16string& text, int textFontSize, const string& src, ResourceManager::Type type);

	void Update(float dt) override;
	void Render() override;
	
private:
	bool						m_isPressed = false;
	bool						m_isTextVisible = false;
	function<bool()>			m_onClick;
	Label					  * m_label = nullptr;
	
	bool IsMouseInside();
};