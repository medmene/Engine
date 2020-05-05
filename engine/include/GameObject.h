#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "ResourceManager.h"


class Animator;

class GameObject
{
protected:
	explicit GameObject();
	bool CreateSettings(const string & src, ResourceManager::Type type);
	bool LoadSettings(const string & src, ResourceManager::Type type);
	bool LoadSettings();
public:
	virtual ~GameObject();
	GameObject(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);

	bool IsVisible() { return m_visible; }
	bool IsFollowVisibility() { return m_followVisibility; }
	bool IsFollowStatic() { return m_followStatic; }
	bool IsStaticObject() { return m_staticObject; }
	bool IsAnimationEnabled();

	void SetParent(GameObject * parent) { m_parent = parent; }
	void SetVisible(bool visible) { m_visible = visible; }
	void SetFollowVisibility(bool follow) { m_followVisibility = follow; }
	void SetFollowStatic(bool follow) { m_followStatic = follow; }
	void SetStaticObject(bool stObj) { m_staticObject = stObj; }
	void SetAnimationEnable(bool anim);

	GameObject * GetParent() { return m_parent; }
	const Vector2 & GetCenterPos() { return m_center; }
	const Vector2 & GetPosition() { return m_position; }
	const Vector2 & GetRelativePos() { return m_relativePos; }
	const Vector2 & GetSize() { return m_size; }
	const Color & GetColor() { return m_color; }
	string GetName();
	Animator * GetAnimator() { return m_animator; }

	void UpdateColor(const Color & clr);
	void UpdateSize(const Vector2 & size);
	void UpdatePos(const Vector2 & pos);
	void UpdateCenterPos(const Vector2 & pos);
	void UpdateRelativePos(const Vector2 & pos);
	
	virtual void Update(float dt);
	virtual void Render();
	
protected:
	Resource				  * m_resourceSettings = nullptr;
	Resource				  * m_resourceTexture = nullptr;
	SDL_Renderer			  * m_renderer = nullptr;
	SDL_Texture 			  * m_texture = nullptr;
	GameObject				  * m_parent = nullptr;
	
	SDL_Rect					m_rect;
	Vector2						m_center;
	Color						m_color;
	Vector2						m_position;
	Vector2						m_relativePos; // relative pos of center parent
	Vector2						m_size;
	bool						m_visible;
	bool						m_staticObject;
	bool						m_followVisibility = false;
	bool						m_followStatic = false;

	Animator				  * m_animator = nullptr;
};