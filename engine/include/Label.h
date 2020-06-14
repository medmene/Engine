#pragma once
#include "Core.h"
#include "ResourceManager.h"
#include "GameObject.h"


class Label : public GameObject
{
public:
	explicit Label();
	
	Label(const string & name);
	~Label();
	void LoadGraphics(pugi::xml_node * node) override;
	void LoadSettings(const string & src);

	void Init(const u16string & text, int fontSize = 24);

	void SetText(const u16string & text);
	void SetFont(const string & src, ResourceManager::Type type);
	void SetFontSize(int fontSize);

	int GetFontSize() { return m_fontSize; }
	
	void Render() override;
private:
	TTF_Font						  * m_font = nullptr;
	int									m_fontSize;
	u16string 							m_text;

	void CreateTexture();
};
