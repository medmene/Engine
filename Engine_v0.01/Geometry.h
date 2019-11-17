#pragma once
#include "sVector3.h"
#include "sBoundingBox.h"
#include "Core.h"

class Renderer;

class Geometry
{
public:
	Geometry();
	~Geometry();

	auto matrix() const { return m_matrix; }
	auto bbox() const { return m_bbox; }

	void SetBoundingBox(const sBoundingBox & boundingBox);
private:
	sVector3				m_matrix;
	sBoundingBox			m_bbox;
	SDL_Rect				m_rect;
	friend class Renderer;
};
