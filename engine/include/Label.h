#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "ResourceManager.h"



class Label
{
public:
	explicit Label();
	Label(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);
	~Label();

	void Init(SDL_Renderer * renderer, const string & text, Vector2 pos = Vector2(),
		int fontSize = 24, Color color = Color( 255, 255, 255, 255 ));

	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	void SetText(const string & text);
	void SetFont(const string & src, ResourceManager::Type type);
	void SetFontSize(int fontSize);

	SDL_Texture * GetTexture() { return m_texture; }
	const SDL_Rect & GetRenderRect() { return m_rect; }
	const Vector2 & GetPos() { return m_position; }
	const Color & GetColor() { return m_color; }

	void UpdatePos(const Vector2 & pos);
	void UpdateColor(const Color & color);
	void Update() {}

	void Draw();
private:
	Resource						  * m_resource = nullptr;
	SDL_Renderer					  * m_renderer = nullptr;
	SDL_Texture						  * m_texture = nullptr;
	TTF_Font						  * m_font = nullptr;
	SDL_Rect							m_rect;
	Vector2								m_position;
	bool								m_visible;

	int									m_fontSize;
	Color 								m_color;
	string								m_text;

	void CreateTexture();
};