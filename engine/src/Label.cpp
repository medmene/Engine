#include "include/Label.h"
#include "include/Camera.h"




Label::Label()
	: m_fontSize(24)
	, m_color({ 255, 255, 255, 255 })
	, m_fontName("times.ttf")
	, m_text("_")
	, m_position(0,0)
	, m_visible(true)
{
}

Label::~Label()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void Label::Init(SDL_Renderer * renderer, const string & text, Vector2 pos, string font, int fontSize, Color color)
{
	m_renderer = renderer;
	m_fontSize = fontSize;
	m_fontName = font;
	m_color = color;
	m_position = pos;
	m_text = text;
	CreateTexture(true);
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

void Label::UpdateColor(const Color & color)
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

void Label::Draw()
{
	if (IsVisible())
	{
		SDL_Rect localRect = GetRenderRect();

		localRect.x = localRect.x + Camera::instance()->GetDiff().x;
		localRect.y = localRect.y + Camera::instance()->GetDiff().y;

		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		SDL_RenderCopy(m_renderer, m_texture, nullptr, &localRect);
	}
}

void Label::CreateTexture(bool firstTime)
{
	if (m_renderer)
	{
		string some = std::filesystem::current_path().generic_string() + "/../resources/fonts/" + m_fontName;
		TTF_Font* font = TTF_OpenFont((some).c_str(), m_fontSize);
		if (font) 
		{
			SDL_Color clr = { m_color.GetR(), m_color.GetG(), m_color.GetB() };
			SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, m_text.c_str(), clr);
			if (surfaceMessage)
			{
				if (m_texture && !firstTime)
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

				SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(m_texture, m_color.GetA());
				return;
			}
		}
	}
	throw std::exception();
}
