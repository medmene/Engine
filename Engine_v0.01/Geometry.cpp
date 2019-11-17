#include  "Geometry.h"


Geometry::Geometry()
	: m_matrix()
	, m_bbox()
{
	auto position = m_bbox.position();
	auto size = m_bbox.position();
	m_rect.x = position.get_x_int();
	m_rect.y = position.get_y_int();
	m_rect.w = size.get_x_int();
	m_rect.h = size.get_y_int();
}


Geometry::~Geometry()
{
}

void Geometry::SetBoundingBox(const sBoundingBox& boundingBox)
{
	m_bbox = boundingBox;
	auto position = m_bbox.position();
	auto size = m_bbox.size();
	m_rect.x = position.get_x_int();
	m_rect.y = position.get_y_int();
	m_rect.w = size.get_x_int();
	m_rect.h = size.get_y_int();
}
