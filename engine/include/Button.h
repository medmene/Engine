#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"

class Label;

class Button
{
public:
	Button();
	~Button();

	void Init(SDL_Renderer * renderer, string src = "",
		shared_ptr<Label> lbl = nullptr, Color color = Color(255, 255, 255, 255));

	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	void SetLabel(shared_ptr<Label> lbl) { m_label = lbl; }

	SDL_Texture * GetTexture();
	const SDL_Rect & GetRenderRect() { return m_rect; }
	const Vector2 & GetPos() { return m_position; }
	const Color & GetColor() { return m_color; }
	shared_ptr<Label> GetText() { return m_label; }

	void UpdatePos(const Vector2 & pos);
	void UpdateColor(const Color & color);
	void UpdateSize(const Vector2 & size);
	void Update();
private:
	SDL_Texture						  * m_textureP;
	SDL_Texture						  * m_textureN;
	SDL_Rect							m_rect;
	SDL_Point							m_center;
	Vector2								m_position;
	Vector2								m_size;
	bool								m_visible;
	bool								m_pressed;

	shared_ptr<Label>					m_label;
	Color 								m_color;

	SDL_Renderer					  * m_renderer;
};