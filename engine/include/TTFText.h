#pragma once
#include "Core.h"
#include "Vector2.h"


class TTFText
{
public:
	TTFText();
	~TTFText();

	void Init(SDL_Renderer * renderer, string font = "Sans.ttf", 
		int fontSize = 14, SDL_Color color = { 0,0,0 });

	void SetText(const string & text) { m_text = text; CreateTexture(); }
	void SetFont(const string & font) { m_fontName = font; CreateTexture(); }
	void SetFontSize(int fontSize) { m_fontSize = fontSize; CreateTexture(); }
	void SetColor(SDL_Color color) { m_color = color; CreateTexture(); }

	SDL_Texture * GetTexture() { return m_texture; }
	SDL_Rect GetRenderRect() { return m_rect; }

	void UpdatePos(const Vector2 & pos);

private:
	SDL_Texture						  * m_texture;
	SDL_Rect							m_rect;
	Vector2								m_position;

	int									m_fontSize;
	string								m_fontName;
	SDL_Color 							m_color;
	string								m_text;

	SDL_Renderer					  * m_renderer;

	void CreateTexture();
};