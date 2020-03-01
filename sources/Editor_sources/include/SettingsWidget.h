#pragma once
#include "Include/Core.h"
#include "Include/Vector2.h"
#include "Include/GameObject.h"

class EditorWindow;

class SettingsWidget
{
public:
	SettingsWidget();
	~SettingsWidget();
	void Init(EditorWindow* editor);

	const string & GetSelected();
	void Draw();

private:
	SDL_Renderer				  * m_renderer;
	bool							m_settingsActive;
	Vector2							m_widgetPos;
	Vector2							m_widgetSize;

	// Background
	SDL_Texture					  * m_bg;
	SDL_Rect						m_bgRect;
	
	// Place with resources
	Vector2							m_resourcePos;
	SDL_Rect						m_resourceFrameRect;
	vector<GameObject*>				m_resourceObjects;
	string							m_selected;

	
	EditorWindow				  * m_editor;


	void DrawTexture(SDL_Texture * texture, const SDL_Rect & rect);
};