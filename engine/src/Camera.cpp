#include "include/Camera.h"



Camera * Camera::sm_instance = new Camera();

Camera::Camera()
	: m_position(0, 0)
	, m_diff(0, 0)
	, m_zoom(1.f)
	, m_zoomBorders(0.1f, 3.f)
{
}

void Camera::UpdateZoom(int zoomDir)
{
	m_zoom += 0.1f * zoomDir;
	if (m_zoom < m_zoomBorders.x)
	{
		m_zoom = m_zoomBorders.x;
	}
	if (m_zoom > m_zoomBorders.y)
	{
		m_zoom = m_zoomBorders.y;
	}
}
