#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"

class GameObject
{
public:
	explicit GameObject();
	~GameObject();
	GameObject(SDL_Renderer * renderer, const string & src);

	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	SDL_Texture * GetTexture() { return m_texture; }
	const SDL_Rect & GetRenderRect();
	const Vector2 & GetCenterPos() { return m_center; }
	const Vector2 & GetPosition() { return m_position; }
	const Vector2 & GetSize() { return m_size; }
	double GetAngle() { return m_angle; }
	const Color & GetColor() { return m_color; }

	void UpdateColor(const Color & clr);
	void UpdateSize(const Vector2 & size);
	void UpdatePos(const Vector2 & pos);
	void UpdateAngle(double angle) { m_angle = angle; }
private:
	SDL_Texture 			  * m_texture;
	SDL_Rect					m_rect;
	double						m_angle;
	string						m_resourceName;
	Vector2						m_center;
	Color						m_color;

	Vector2						m_position;
	Vector2						m_size;
	bool						m_visible;
	bool						m_enabled;
};