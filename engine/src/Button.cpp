#include "include/Button.h"
#include "include/Label.h"


Button::Button()
	: m_visible(true)
	, m_position(0, 0)
	, m_rect({ 0, 0, 0, 0 })
	, m_color({ 255, 255, 255, 255 })
	, m_animationEnabled(true)
{
}

Button::~Button()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

Button::Button(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: m_visible(true)
	, m_position(0, 0)
	, m_rect({ 0, 0, 0, 0 })
	, m_color({ 255, 255, 255, 255 })
	, m_animationEnabled(true)
{
	// m_renderer = renderer;
	// m_resource = ResourceManager::instance()->GetResource(src, type);
	//
	// if (m_resource)
	// {
	// 	auto surface = IMG_Load(m_resource->GetPath().c_str());
	// 	
	// 	if (surface)
	// 	{
	// 		m_rect = surface->clip_rect;
	// 		
	// 		if (m_rect.w % m_rect.h == 0)
	// 		{
	// 			m_size = { m_rect.w, m_rect.h };
	//
	// 			m_center = Vector2(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
	// 			m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	// 			SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
	// 			SDL_FreeSurface(surface);
	// 			return;
	// 		}
	// 	}
	// }
	// throw std::exception();
}

// void Button::Init(SDL_Renderer * renderer, string src, shared_ptr<Label> lbl, Color color)
// {
// 	m_renderer = renderer;
// 	m_color = color;
// 	if (m_renderer)
// 	{
// 		string normal;
// 		string pressed;
// 		if (src.empty())
// 		{
// 			normal = std::filesystem::current_path().generic_string() + "/../resources/button/def_button.png";
// 			pressed = std::filesystem::current_path().generic_string() + "/../resources/button/p_def_button.png";
// 		}
// 		else
// 		{
// 			normal = std::filesystem::current_path().generic_string() + "/../resources/fonts/" + src;
// 			pressed = std::filesystem::current_path().generic_string() + "/../resources/fonts/p_" + src;
// 		}
// 	
// 		auto surfaceNor = IMG_Load((normal).c_str());
// 		auto surfacePrs = IMG_Load((pressed).c_str());
// 	
// 		if (surfaceNor && surfacePrs)
// 		{
// 			m_rect = surfaceNor->clip_rect;
// 			m_size = { m_rect.w, m_rect.h };
// 			m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
// 			m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
// 			m_textureP = SDL_CreateTextureFromSurface(renderer, surfacePrs);
// 			m_textureN = SDL_CreateTextureFromSurface(renderer, surfaceNor);
// 			SDL_SetTextureBlendMode(m_textureP, SDL_BLENDMODE_BLEND);
// 			SDL_SetTextureBlendMode(m_textureN, SDL_BLENDMODE_BLEND);
// 			SDL_FreeSurface(surfaceNor);
// 			SDL_FreeSurface(surfacePrs);
// 		}
// 	}
// }

void Button::UpdatePos(const Vector2 & pos)
{
	// m_position = pos;
	// m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	// m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
}

void Button::UpdateSize(const Vector2 & size)
{
	// m_size = size;
	// m_rect = { (int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y };
	// m_center = { (int)(m_rect.w - m_rect.x) / 2, (int)(m_rect.h - m_rect.y) / 2 };
}

void Button::Update()
{

}

void Button::UpdateColor(const Color & clr)
{
	// m_color = clr;
	//
	// if (m_texture)
	// {
	// 	SDL_SetTextureColorMod(m_texture, m_color.GetR(), m_color.GetG(), m_color.GetB());
	// 	SDL_SetTextureAlphaMod(m_texture, m_color.GetA());
	// }
}

void Button::Render()
{
	
}