#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "ResourceManager.h"
#include "GameObject.h"


class Label : public GameObject
{
public:
	explicit Label();
	
	Label(SDL_Renderer * renderer, const string & src);
	~Label();

	void Init(const string & text, int fontSize = 24);

	void SetText(const string & text);
	void SetFont(const string & src, ResourceManager::Type type);
	void SetFontSize(int fontSize);

	string GetText() { return m_text; }
	int GetFontSize() { return m_fontSize; }
	
	void Render() override;
private:
	TTF_Font						  * m_font = nullptr;
	int									m_fontSize;
	string								m_text;

	void CreateTexture();
};
