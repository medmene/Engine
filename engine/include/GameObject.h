#pragma once
#include "Core.h"
#include "Vector2.h"


class GameObject
{
public:
	explicit GameObject();
	~GameObject();
	GameObject(SDL_Renderer * renderer, string src);

	SDL_Texture * GetTexture() { return m_texture; }
	const SDL_Rect & GetRenderRect();
	const SDL_Point & GetCenterPos() { return m_center; }
	const Vector2 & GetPosition() { return m_position; }
	double GetAngle() { return m_angle; }

	void UpdateSize(const Vector2 & size);
	void UpdatePos(const Vector2 & pos);
	void UpdateAngle(double angle) { m_angle = angle; }
private:
	SDL_Texture 			  * m_texture;
	SDL_Rect					m_rect;
	double						m_angle;
	string						m_resourceName;
	SDL_Point					m_center;

	Vector2						m_position;
	Vector2						m_size;
	bool						m_visible;
	bool						m_enabled;
};