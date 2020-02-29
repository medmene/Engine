#pragma once
#include "Vector2.h"


class Camera 
{
public:
	Camera();
	~Camera(){}
	void Initialize(const Vector2 & diff) { m_diff = diff; }
	static Camera * instance() { return sm_instance; }

	void UpdatePos(const Vector2 & diff) { m_position += diff; }
	const Vector2 & GetPosition() { return m_position; }

	void UpdateZoom(int zoomDir);
	float GetZoom() { return m_zoom; }
private:
	Vector2						m_position;
	Vector2						m_diff;

	float						m_zoom;
	Vector2						m_zoomBorders;

	static Camera			  * sm_instance;
};