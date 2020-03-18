#include "include/Button.h"
#include "include/Label.h"


Button::Button()
	: m_color({ 255, 255, 255, 255 })
	, m_position(0, 0)
	, m_visible(true)
	, m_pressed(false)
	, m_size(10, 10)
{
}

Button::~Button()
{
	if (m_textureP)
	{
		SDL_DestroyTexture(m_textureP);
	}
	if (m_textureN)
	{
		SDL_DestroyTexture(m_textureN);
	}
}

void Button::Init(SDL_Renderer * renderer, string src, shared_ptr<Label> lbl, Color color)
{
	m_renderer = renderer;
	//m_label = lbl;
	m_color = color;
	if (m_renderer)
	{
		string normal;
		string pressed;
		if (src.empty())
		{
			normal = std::filesystem::current_path().generic_string() + "/../resources/button/def_button.png";
			pressed = std::filesystem::current_path().generic_string() + "/../resources/button/p_def_button.png";
		}
		else
		{
			normal = std::filesystem::current_path().generic_string() + "/../resources/fonts/" + src;
			pressed = std::filesystem::current_path().generic_string() + "/../resources/fonts/p_" + src;
		}

		auto surfaceNor = IMG_Load((normal).c_str());
		auto surfacePrs = IMG_Load((pressed).c_str());

		if (surfaceNor && surfacePrs)
		{
			m_rect = surfaceNor->clip_rect;
			m_size = { m_rect.w, m_rect.h };
			m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
			m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
			m_textureP = SDL_CreateTextureFromSurface(renderer, surfacePrs);
			m_textureN = SDL_CreateTextureFromSurface(renderer, surfaceNor);
			SDL_SetTextureBlendMode(m_textureP, SDL_BLENDMODE_BLEND);
			SDL_SetTextureBlendMode(m_textureN, SDL_BLENDMODE_BLEND);
			SDL_FreeSurface(surfaceNor);
			SDL_FreeSurface(surfacePrs);
		}
	}
}

SDL_Texture * Button::GetTexture()
{
	return m_pressed ? m_textureP : m_textureP;
}

void Button::UpdatePos(const Vector2 & pos)
{
	m_position = pos;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
	// TODO add text label to button
	/*if (m_label)
	{
		m_label->UpdatePos(pos);
	}*/
}

void Button::UpdateSize(const Vector2 & size)
{
	m_size = size;
	m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
}

void Button::Update()
{

}

void Button::UpdateColor(const Color & clr)
{
	m_color = clr;
	if (m_textureP && m_textureN)
	{
		SDL_SetTextureColorMod(m_textureP, m_color.GetR(), m_color.GetG(), m_color.GetB());
		SDL_SetTextureAlphaMod(m_textureP, m_color.GetA());
		SDL_SetTextureColorMod(m_textureN, m_color.GetR(), m_color.GetG(), m_color.GetB());
		SDL_SetTextureAlphaMod(m_textureN, m_color.GetA());
	}
}
