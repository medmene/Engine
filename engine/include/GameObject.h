#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "ResourceManager.h"
#include "Event.h"


class Animator;

class GameObject
{
public:
	explicit GameObject();
	~GameObject();
	GameObject(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);

	bool IsVisible() { return m_visible; }
	bool IsGravityEnabled() { return m_gravity; }
	bool IsStaticObject() { return m_staticObject; }
	bool IsAnimationEnabled();
	
	void SetVisible(bool visible) { m_visible = visible; }
	void SetGravity(bool gravity) { m_gravity = gravity; }
	void SetStaticObject(bool stObj) { m_staticObject = stObj; }
	void SetAnimationEnable(bool anim);

	SDL_Texture * GetTexture() { return m_texture; }
	const Vector2 & GetCenterPos() { return m_center; }
	const Vector2 & GetPosition() { return m_position; }
	const Vector2 & GetSize() { return m_size; }
	const Color & GetColor() { return m_color; }
	Animator * GetAnimator() { return m_animator; }

	void UpdateColor(const Color & clr);
	void UpdateSize(const Vector2 & size);
	void UpdatePos(const Vector2 & pos);
	void Update(float dt);

	void Render();

	void Subscribe(Event *e, function<void(GameObject*,Event*)> callback);
	
private:
	Resource				  * m_resourceSettings = nullptr;
	Resource				  * m_resourceTexture = nullptr;
	SDL_Renderer			  * m_renderer = nullptr;
	SDL_Texture 			  * m_texture = nullptr;
	SDL_Rect					m_rect;
	Vector2						m_center;
	Color						m_color;

	Animator				  * m_animator;
	
	Vector2						m_position;
	Vector2						m_size;
	bool						m_visible;
	bool						m_staticObject;
	
	bool						m_gravity = false;
	Vector2						m_gravityValue;
};