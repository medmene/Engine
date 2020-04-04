#pragma once
#include "Vector2.h"


class Camera 
{
public:
	Camera();
	~Camera(){}
	void Initialize(const Vector2 & posInWindow) { m_posInWindow = posInWindow; }
	static Camera * instance() { return sm_instance; }

	void UpdatePos(const Vector2 & diff) { m_position += diff; }
	void SetPos(const Vector2 & pos) { m_position = pos; }
	Vector2 GetDiff() { return m_posInWindow - m_position; }
	//const Vector2 & GetPosition() { return m_position; }
	const Vector2 & GetPositionInWindow() { return m_posInWindow; }

	void UpdateZoom(int zoomDir);
	float GetZoom() { return m_zoom; }
private:
	Vector2						m_position;
	Vector2						m_posInWindow;

	float						m_zoom;
	Vector2						m_zoomBorders;

	static Camera			  * sm_instance;
};