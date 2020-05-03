#include "include/Camera.h"
#include "include/GameObject.h"


Camera * Camera::sm_instance = nullptr;

Camera::Camera()
	: m_position(0, 0)
	, m_posInWindow(0, 0)
	, m_zoom(1.f)
	, m_zoomEnabled(false)
	, m_zoomBorders(0.1f, 3.f)
{
}

Camera* Camera::instance()
{
	if (!sm_instance)
	{
		sm_instance = new Camera();
	}
	return sm_instance;
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

void Camera::Update(float dt)
{
	m_position = m_followingObject->GetCenterPos();
}
