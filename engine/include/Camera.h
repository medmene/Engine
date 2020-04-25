#pragma once
#include "Vector2.h"


class Camera 
{
public:
	Camera();
	~Camera(){}
	
	void Initialize(const Vector2 & posInWindow) { m_posInWindow = posInWindow; }
	static Camera * instance() { return sm_instance; }

	bool IsZoomEnabled() { return m_zoomEnabled; }
	void SetPos(const Vector2 & pos) { m_position = pos; }
	
	Vector2 GetDiff() { return m_posInWindow - m_position; }
	float GetZoom() { return m_zoom; }
	const Vector2 & GetPositionInWindow() { return m_posInWindow; }

	void UpdatePos(const Vector2 & diff) { m_position += diff; }
	void UpdateZoom(int zoomDir);
private:
	Vector2						m_position;
	Vector2						m_posInWindow;

	float						m_zoom;
	Vector2						m_zoomBorders;
	bool						m_zoomEnabled;

	static Camera			  * sm_instance;
};