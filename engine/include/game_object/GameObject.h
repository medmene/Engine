#pragma once
#include "include/game_object/BaseObject.h"
#include "include/types/Color.h"


class Animator;
class Resource;

namespace pugi
{
	class xml_node;
}

class GameObject : public BaseObject
{
protected:
	explicit GameObject();
	void LoadSettings(pugi::xml_node * node);
public:
	virtual ~GameObject();
	GameObject(const string & name);
	virtual void LoadGraphics(pugi::xml_node * node);

	bool IsVisible() { return m_visible; }
	bool IsFollowVisibility() { return m_followVisibility; }
	bool IsFollowStatic() { return m_followStatic; }
	bool IsStaticObject() { return m_staticObject; }
	bool IsAnimationEnabled();

	void SetParent(GameObject * parent) { m_parent = parent; }
	void SetAnimationEnable(bool anim);

	void SetVisible(bool visible) { m_visible = visible; }
	void SetStaticObject(bool stObj) { m_staticObject = stObj; }
	void SetFollowVisibility(bool follow) { m_followVisibility = follow; }
	void SetFollowStatic(bool follow) { m_followStatic = follow; }

	GameObject * GetParent() const { return m_parent; }
	Vector2 GetCenterPos() const { return m_center; }
	Vector2 GetPosition() const { return m_position; }
	Vector2 GetRelativePos() const { return m_relativePos; }
	Vector2 GetSize() const { return m_size; }
	Vector2 GetPivotPos() const { return m_pivot; }
	Color GetColor() const { return m_color; }
	string GetName();
	Animator * GetAnimator() { return m_animator; }

	void UpdateColor(const Color & clr);
	void UpdateSize(const Vector2 & size);
	virtual void UpdatePos(const Vector2 & pos);
	void UpdateCenterPos(const Vector2 & pos);
	void UpdateRelativePos(const Vector2 & pos);
	
	virtual void Update(float dt);
	virtual void Render();
	
protected:
	Resource				  * m_resourceTexture = nullptr;
	SDL_Texture 			  * m_texture = nullptr;
	GameObject				  * m_parent = nullptr;

	string						m_name;
	SDL_Rect					m_rect;
	Vector2						m_center;
	Color						m_color;
	Vector2						m_position;
	Vector2						m_relativePos;	// relative pos of center parent
	Vector2						m_size;
	Vector2						m_pivot;		// position of connecting with ground
	Vector2						m_pivotOffset;	// offset relative center
	bool						m_visible;
	bool						m_staticObject;
	bool						m_followVisibility;
	bool						m_followStatic;

	Animator				  * m_animator = nullptr;
};