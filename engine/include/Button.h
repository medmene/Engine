#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Color.h"
#include "Label.h"
#include "GameObject.h"
#include "ResourceManager.h"

class Animator;
class Label;
class GameObject;

class Button : public GameObject
{
public:
	explicit Button();
	~Button();
	Button(SDL_Renderer * renderer, const string & src, ResourceManager::Type type);

	// void Init(SDL_Renderer * renderer, string src = "",
	// 	shared_ptr<Label> lbl = nullptr, Color color = Color(255, 255, 255, 255));

	bool IsVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	//void SetAnimationEnable(bool anim, int animCount);

	const Vector2 & GetPos() { return m_position; }
	const Color & GetColor() { return m_color; }
	const Label & GetLabel() { return m_label; }

	void UpdatePos(const Vector2 & pos);
	void UpdateColor(const Color & color);
	void UpdateSize(const Vector2 & size);
	void Update(float dt);
	bool IsMouseInside();

	void Render();
	
private:
	Resource						  * m_resourceTexture = nullptr;
	Resource						  * m_resource = nullptr;
	SDL_Renderer					  * m_renderer = nullptr;
	SDL_Texture						  * m_texture = nullptr;
	SDL_Rect							m_rect;
	Vector2								m_center;
	Vector2								m_position;
	Vector2								m_size;
	bool								m_visible;
	bool								m_staticObject;
	bool								m_isPressed = false;
	Color 								m_color;
	Label							    m_label;
	
	Animator				  		  * m_animator;
};