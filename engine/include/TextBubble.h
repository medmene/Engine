#pragma once
#include "GameObject.h"

class Label;

class TextBubble : public GameObject
{
public:
	enum BubbleSide
	{
		RIGHT = 0,
		LEFT
	};
	
	TextBubble(const string & src);
	~TextBubble();
	
	void SetSide(BubbleSide s);
	void SetFontSize(int fSize) { m_fontSize = fSize; }
	void SetText(const u16string & text);
	
	BubbleSide GetSide() { return m_currentSide; }
	int GetFontSize() { return m_fontSize; }

	void Update(float dt) override;
	void Render() override;
private:
	BubbleSide					m_currentSide;
	Vector2						m_defaultRelPos;
	Vector2						m_textCenterPos;
	u16string					m_text;
	vector<Label*>				m_labels;
	int							m_fontSize;

	void DestroyLabels();
};