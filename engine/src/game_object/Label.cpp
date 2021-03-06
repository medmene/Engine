#include "include/game_object/Label.h"
#include "include/input/Camera.h"
#include "pugixml/pugixml.hpp"
#include "include/tools/Utils.h"




Label::Label()
	: GameObject()
	, m_fontSize(24)
	, m_text(u"_")
{
}

Label::Label(const string & name)
	: GameObject(name)
	, m_fontSize(24)
	, m_text(u"_")
{
}

Label::~Label()
{
	if (m_font) { TTF_CloseFont(m_font); }
}

void Label::LoadGraphics(pugi::xml_node * node)
{
	GameObject::LoadSettings(node);

	// Text
	if (!node->attribute("text").empty())
	{
		string value = node->attribute("text").value();
		m_text = u16string(value.begin(), value.end());
	}

	// Font size
	if (!node->attribute("font_size").empty())
	{
		m_fontSize = std::stoi(node->attribute("font_size").value());
	}

	if (m_resourceTexture)
	{
		if (m_font)
		{
			TTF_CloseFont(m_font);
		}
		m_font = TTF_OpenFont(m_resourceTexture->GetPath().c_str(), m_fontSize);
		if (m_font)
		{
			CreateTexture();
		}
		return;
	}
	throw std::exception();
}

void Label::LoadSettings(const string & src)
{
	m_resourceTexture = ResourceManager::instance()->GetResource(src);
	if (m_resourceTexture)
	{
		if (m_font)
		{
			TTF_CloseFont(m_font);
		}
		m_font = TTF_OpenFont(m_resourceTexture->GetPath().c_str(), m_fontSize);
		if (m_font)
		{
			CreateTexture();
		}
		return;
	}
	throw std::exception();
}

void Label::Init(const u16string & text, int fontSize)
{
	if (fontSize != m_fontSize)
	{
		m_fontSize = fontSize;
		if (m_resourceTexture)
		{
			if (m_font)
			{
				TTF_CloseFont(m_font);
			}
			m_font = TTF_OpenFont(m_resourceTexture->GetPath().c_str(), m_fontSize);
			if (m_font)
			{
				CreateTexture();
			}
		}
	}
	
	m_text = text;
	CreateTexture();
}

void Label::SetText(const u16string & text)
{
	m_text = text;
	CreateTexture();
}

void Label::SetFont(const string & src, ResourceManager::Type type)
{
	m_resourceTexture = ResourceManager::instance()->GetResource(src, type);

	if (m_resourceTexture)
	{
		if (m_font)
		{
			TTF_CloseFont(m_font);
		}
		m_font = TTF_OpenFont(m_resourceTexture->GetPath().c_str(), m_fontSize);
		if (m_font)
		{
			CreateTexture();
		}
		return;
	}
	throw std::exception("Can't setup font");
}

void Label::SetFontSize(int fontSize)
{
	m_fontSize = fontSize;
	if (m_font)
	{
		TTF_CloseFont(m_font);
	}
	m_font = TTF_OpenFont(m_resourceTexture->GetPath().c_str(), m_fontSize);
	CreateTexture();
}

void Label::Render()
{
	if (IsVisible())
	{
		SDL_Rect localRect = m_rect;
		
		if (!m_staticObject)
		{
			localRect.x *= Camera::instance()->GetZoom();
			localRect.y *= Camera::instance()->GetZoom();
			localRect.w *= Camera::instance()->GetZoom();
			localRect.h *= Camera::instance()->GetZoom();
			
			// Apply camera moving
			auto diff = Camera::instance()->GetDiff();
			localRect.x = localRect.x + diff.x;
			localRect.y = localRect.y + diff.y;
		}

		SDL_RenderCopy(m_renderer, m_texture, nullptr, &localRect);
	}
}

void Label::CreateTexture()
{
	if (m_renderer && m_font)
	{
		SDL_Color clr = { m_color.GetR(), m_color.GetG(), m_color.GetB() };
		SDL_Surface* surfaceMessage = TTF_RenderUNICODE_Solid(m_font, (Uint16*)m_text.c_str(), clr);
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

			UpdateSize(Vector2(surfaceMessage->w, surfaceMessage->h));
			
			if (surfaceMessage)
			{
				SDL_FreeSurface(surfaceMessage);
			}

			SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(m_texture, m_color.GetA());
			return;
		}
	}
	throw std::exception("Error in smth mb text is empty");
}
