#pragma once

class Property
{
public:
	Property();

	void SetVisible(bool visible) {	m_visible = visible; }
	void SetEnabled(bool enabled) { m_enabled = enabled; }
	bool IsVisible() { return m_visible; }
	bool IsEnabled() { return m_enabled; }
	
private:
	bool			m_enabled;
	bool			m_visible;	
};

