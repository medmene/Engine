#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "ResourceManager.h"

class GameObject
{
public:
	explicit GameObject();
	~GameObject();
	GameObject(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);

	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	SDL_Texture * GetTexture() { return m_texture; }
	const SDL_Rect & GetRenderRect() { return m_rect; } 
	const Vector2 & GetCenterPos() { return m_center; }
	const Vector2 & GetPosition() { return m_position; }
	const Vector2 & GetSize() { return m_size; }
	double GetAngle() { return m_angle; }
	const Color & GetColor() { return m_color; }

	void UpdateColor(const Color & clr);
	void UpdateSize(const Vector2 & size);
	void UpdatePos(const Vector2 & pos);
	void UpdateAngle(double angle) { m_angle = angle; }
	void Update(float dt);

	void Draw();
private:
	Resource				  * m_resource;
	SDL_Renderer			  * m_renderer;
	SDL_Texture 			  * m_texture;
	SDL_Rect					m_rect;
	double						m_angle;
	Vector2						m_center;
	Color						m_color;

	Vector2						m_position;
	Vector2						m_size;
	bool						m_visible;
	bool						m_enabled;

	int							m_animationIndex = 0;
	int							m_animationCount;
	float						m_animationFrameTime;
	float						m_counter;
};