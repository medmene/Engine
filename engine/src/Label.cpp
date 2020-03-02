#include "include/Label.h"




Label::Label()
	: m_fontSize(14)
	, m_color({ 0, 0, 0, 0 })
	, m_fontName("Sans.ttf")
	, m_text("")
	, m_position(0,0)
{
}

Label::~Label()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void Label::Init(SDL_Renderer * renderer, Vector2 pos, string font, int fontSize, SDL_Color color)
{
	m_renderer = renderer;
	m_fontSize = fontSize;
	m_fontName = font;
	m_color = color;
	m_position = pos;
	CreateTexture();
}

void Label::SetText(const string & text)
{
	m_text = text;
	CreateTexture();
}

void Label::SetFont(const string & font)
{
	m_fontName = font;
	CreateTexture();
}

void Label::SetFontSize(int fontSize)
{
	m_fontSize = fontSize;
	CreateTexture();
}

void Label::SetColor(const SDL_Color & color)
{
	m_color = color;
	CreateTexture();
}

void Label::UpdatePos(const Vector2 & pos)
{
	m_position = pos;
	m_rect.x = m_position.x;
	m_rect.y = m_position.y;
}

void Label::CreateTexture()
{
	if (m_renderer)
	{
		TTF_Font* font = TTF_OpenFont(m_fontName.c_str(), m_fontSize);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, m_text.c_str(), m_color);

		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}
		m_texture = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

		m_rect.x = m_position.x;
		m_rect.y = m_position.y;
		m_rect.w = surfaceMessage->w;
		m_rect.h = surfaceMessage->h;
		if (surfaceMessage)
		{
			SDL_FreeSurface(surfaceMessage);
		}
	}
}
