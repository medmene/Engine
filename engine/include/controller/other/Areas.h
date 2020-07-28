#pragma once
#include "include/Core.h"
#include "include/types/Vector2.h"


class PassabilityArea
{
public:
	PassabilityArea();
	PassabilityArea(const Vector2 & pos, float rad);
	void UpdatePos(const Vector2 & pos);

	vector<Vector2> GetWorldPoses() const { return m_worldPos; }
	Vector2 GetPos() const { return m_pos; }
	float GetRadius() { return m_radius; }

private:
	Vector2				m_pos;
	float				m_radius;
	vector<Vector2>		m_worldPos;
};

class TriggerArea
{
public:
	TriggerArea() = default;
private:
	vector<Vector2>			m_corners;
};

class LadderArea
{
public:
	static void SetupAreaSettings(float movingSpeedDebuff, float animSpeedDebiff);

	static float GetAnimSpeedDebuff() { return m_animSpeedDebuff; }
	static float GetMovingSpeedDebuff() { return m_movingSpeedDebuff; }
private:
	LadderArea() = default;
	static float			m_movingSpeedDebuff;
	static float			m_animSpeedDebuff;
};