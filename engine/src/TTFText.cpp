#include "include/TTFText.h"




TTFText::TTFText()
	: m_fontSize(14)
	, m_color({ 0, 0, 0 })
	, m_fontName("Sans.ttf")
	, m_text("")
{
}

TTFText::~TTFText()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void TTFText::Init(SDL_Renderer * renderer, string font, int fontSize, SDL_Color color)
{
	m_renderer = renderer;
	m_fontSize = fontSize;
	m_fontName = font;
	m_color = color;
	CreateTexture();
}

void TTFText::CreateTexture()
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
		if (surfaceMessage)
		{
			SDL_FreeSurface(surfaceMessage);
		}

		m_rect.x = 0;  //controls the rect's x coordinate 
		m_rect.y = 0; // controls the rect's y coordinte
		m_rect.w = 100; // controls the width of the rect
		m_rect.h = 100; // controls the height of the rect
	}
}
