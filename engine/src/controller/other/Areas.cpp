#include "include/controller/other/Areas.h"




PassabilityArea::PassabilityArea()
	: m_pos(Vector2::zero)
	, m_radius(0.f)
{
}

PassabilityArea::PassabilityArea(const Vector2& pos, float rad)
	: m_pos(pos)
	, m_radius(rad)
{
	const int cornerOffset = (int)sqrt(m_radius * m_radius / 2);

	Vector2 posLeft = m_pos; posLeft.x -= m_radius;
	Vector2 posTopLeft = m_pos; posTopLeft.x -= cornerOffset; posTopLeft.y -= cornerOffset;
	Vector2 posTop = m_pos; posTop.y -= m_radius;
	Vector2 posTopRight = m_pos; posTopRight.x += cornerOffset; posTopRight.y -= cornerOffset;
	Vector2 posRight = m_pos; posRight.x += m_radius;
	Vector2 posBottomRight = m_pos; posBottomRight.x += cornerOffset; posBottomRight.y += cornerOffset;
	Vector2 posBottom = m_pos; posBottom.y += m_radius;
	Vector2 posBottomLeft = m_pos; posBottomLeft.x -= cornerOffset; posBottomLeft.y += cornerOffset;

	m_worldPos.emplace_back(posLeft);
	m_worldPos.emplace_back(posTopLeft);
	m_worldPos.emplace_back(posTop);
	m_worldPos.emplace_back(posTopRight);
	m_worldPos.emplace_back(posRight);
	m_worldPos.emplace_back(posBottomRight);
	m_worldPos.emplace_back(posBottom);
	m_worldPos.emplace_back(posBottomLeft);
}

void PassabilityArea::UpdatePos(const Vector2& pos)
{
	auto oldPos = m_pos;
	m_pos = pos;
	for (auto && corner : m_worldPos)
	{
		corner += m_pos - oldPos;
	}
}


float LadderArea::m_movingSpeedDebuff = 0.f;
float LadderArea::m_animSpeedDebuff = 0.f;

void LadderArea::SetupAreaSettings(float movingSpeedDebuff, float animSpeedDebiff)
{
	m_movingSpeedDebuff = movingSpeedDebuff;
	m_animSpeedDebuff = animSpeedDebiff;
}

// --------------------------------------------------------------------------------------------- //
