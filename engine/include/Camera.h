#pragma once
#include "Vector2.h"

class GameObject;

class Camera 
{
	Camera();
public:
	void Initialize(const Vector2 & posInWindow) { m_posInWindow = posInWindow; }
	static Camera * instance();

	bool IsZoomEnabled() { return m_zoomEnabled; }
	void SetFollowingObject(GameObject * obj) { m_followingObject = obj; }
	
	Vector2 GetDiff() { return m_posInWindow - m_position; }
	Vector2 GetPosInWnd() { return m_posInWindow; }
	Vector2 GetPos() { return m_position; }
	float GetZoom() { return m_zoom; }

	void UpdateZoom(int zoomDir);
	void Update(float dt);
private:
	GameObject				  * m_followingObject = nullptr;
	Vector2						m_position;
	Vector2						m_posInWindow;

	float						m_zoom;
	Vector2						m_zoomBorders;
	bool						m_zoomEnabled;

	static Camera			  * sm_instance;
};