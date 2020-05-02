#include "include/Label.h"
#include "include/Camera.h"




Label::Label()
	: m_fontSize(24)
	, m_color({ 255, 255, 255, 255 })
	, m_text("_")
	, m_position(0,0)
	, m_visible(true)
{
}

Label::Label(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: m_fontSize(24)
	, m_color({ 255, 255, 255, 255 })
	, m_text("_")
	, m_position(0, 0)
	, m_visible(true)
{
	m_renderer = renderer;
	m_resource = ResourceManager::instance()->GetResource(src, type);

	if (m_resource)
	{
		m_font = TTF_OpenFont(m_resource->GetPath().c_str(), m_fontSize);
		if (m_font)
		{
			CreateTexture();
		}
		return;
	}
	throw std::exception();
}

Label::~Label()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void Label::Init(SDL_Renderer * renderer, const string & text, Vector2 pos, int fontSize, Color color)
{
	m_renderer = renderer;
	m_fontSize = fontSize;
	m_color = color;
	m_position = pos;
	m_text = text;
	CreateTexture();
}

void Label::SetText(const string & text)
{
	m_text = text;
	CreateTexture();
}

void Label::SetFont(const string & src, ResourceManager::Type type)
{
	m_resource = ResourceManager::instance()->GetResource(src, type);

	if (m_resource)
	{
		m_font = TTF_OpenFont(m_resource->GetPath().c_str(), m_fontSize);
		if (m_font)
		{
			CreateTexture();
		}
		return;
	}
	throw std::exception();
}

void Label::SetFontSize(int fontSize)
{
	m_fontSize = fontSize;
	m_font = TTF_OpenFont(m_resource->GetPath().c_str(), m_fontSize);
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

		auto diff = Camera::instance()->GetDiff();
		localRect.x = localRect.x + diff.x;
		localRect.y = localRect.y + diff.y;

		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		SDL_RenderCopy(m_renderer, m_texture, nullptr, &localRect);
	}
}

void Label::CreateTexture()
{
	if (m_renderer && m_font)
	{
		SDL_Color clr = { m_color.GetR(), m_color.GetG(), m_color.GetB() };
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_font, m_text.c_str(), clr);
		if (surfaceMessage)
		{
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

			SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(m_texture, m_color.GetA());
			return;
		}
	}
	throw std::exception();
}
