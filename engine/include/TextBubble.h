#pragma once
#include "Core.h"
#include "Vector2.h"
#include "GameObject.h"

class Label;

class TextBubble : public GameObject
{
public:
	enum Side
	{
		RIGHT = 0,
		LEFT
	};
	
	TextBubble(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	~TextBubble();
	
	void SetSide(Side s);
	void SetFontSize(int fSize) { m_fontSize = fSize; }
	void SetText(const string & text);
	
	Side GetSide() { return m_currentSide; }
	string GetText() { return m_text; }
	int GetFontSize() { return m_fontSize; }

	void Update(float dt) override;
	void Render() override;
private:
	Side						m_currentSide;
	Vector2						m_defaultRelPos;
	Vector2						m_textCenterPos;
	string						m_text;
	vector<Label*>				m_labels;
	int							m_fontSize;

	void DestroyLabels();
};