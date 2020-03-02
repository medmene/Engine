#pragma once
#include "Core.h"
#include "Vector2.h"


class Label
{
public:
	Label();
	~Label();

	void Init(SDL_Renderer * renderer, Vector2 pos = Vector2(), string font = "Sans.ttf",
		int fontSize = 14, SDL_Color color = { 0,0,0,0 });

	void SetText(const string & text);
	void SetFont(const string & font);
	void SetFontSize(int fontSize);
	void SetColor(const SDL_Color & color);

	SDL_Texture * GetTexture() { return m_texture; }
	const SDL_Rect & GetRenderRect() { return m_rect; }
	const Vector2 & GetPos() { return m_position; }

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