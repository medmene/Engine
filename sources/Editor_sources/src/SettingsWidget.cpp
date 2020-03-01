#include "Editor_sources/include/SettingsWidget.h"
#include "Editor_sources/include/EditorWindow.h"




SettingsWidget::SettingsWidget()
	: m_settingsActive(true)
	, m_widgetPos(0, 0)
	, m_resourcePos(3, 300)
	, m_widgetSize(200, 400)
{
}

SettingsWidget::~SettingsWidget()
{
	if (m_bg)
	{
		SDL_DestroyTexture(m_bg);
	}
	for (auto && res : m_resourceObjects)
	{
		delete res;
	}
	m_resourceObjects.clear();
}

void SettingsWidget::Init(EditorWindow* editor)
{
	m_editor = editor;
	m_renderer = editor->GetRenderer();
	m_widgetSize.y = editor->GetWindowSize().y;

	// Init white background
	SDL_Surface * bg = SDL_CreateRGBSurface(0, m_widgetSize.x, m_widgetSize.y, 32, 0, 0, 0, 0);
	SDL_FillRect(bg, NULL, SDL_MapRGB(bg->format, 255, 255, 255));
	m_bg = SDL_CreateTextureFromSurface(m_renderer, bg);
	m_bgRect = { 0, 0, (int)m_widgetSize.x, (int)m_widgetSize.y };
	SDL_FreeSurface(bg);

	// Init black frame for resources
	m_resourceFrameRect = { (int)m_resourcePos.x, (int)m_resourcePos.y,
		(int)(m_widgetSize.x - 6), (int)(m_widgetSize.y - 202) };

	// Find all resources in dir
	namespace fs = std::filesystem;
	string path = fs::current_path().generic_string() + "/../resources/";
	vector<string> resNames;
	for (auto && entry : fs::directory_iterator(path))
	{
		auto fullName = entry.path().generic_string();
		fullName = fullName.substr(path.size());
		resNames.emplace_back(fullName);
	}
	//std::filesystem::recursive_directory_iterator
	int i = 0;
	bool stop = false;
	int margin = 15;
	int size = 64;
	int minBuffer = size / 3;
	for (int row = 0; ;)
	{
		for (int cell = 0; ; ++cell)
		{
			if (i >= resNames.size()) { stop = true; break; }

			GameObject * obj = new GameObject(m_renderer, resNames[i]);
			obj->UpdateSize(Vector2(size, size));
			obj->UpdatePos(Vector2(m_resourcePos.x + margin + cell * (minBuffer + size), 
				m_resourcePos.y + margin + (minBuffer + size) * row));
			auto nextEndPos = m_resourcePos.x + margin + (cell + 1) * (minBuffer + size) + size;
			if (nextEndPos > m_widgetSize.x - margin)
			{
				++row;
				cell = -1;
			}
			m_resourceObjects.emplace_back(obj);

			i++;
		}
		if (stop) { break; }
	}
	
}

void SettingsWidget::Draw()
{
	// Background
	SDL_RenderCopy(m_renderer, m_bg, nullptr, &m_bgRect);

	// Top left button hide/show


	// Draw rect for resources
	SDL_RenderSetScale(m_renderer, 1, 1);
	SDL_RenderDrawRect(m_renderer, &m_resourceFrameRect);
	SDL_RenderSetScale(m_renderer, 1, 1);

	// Resources
	for (auto && res : m_resourceObjects)
	{
		SDL_RenderCopy(m_renderer, res->GetTexture(), nullptr, &res->GetRenderRect());
	}
}

void SettingsWidget::DrawTexture(SDL_Texture * texture, const SDL_Rect & rect)
{
	SDL_RenderCopy(m_renderer, texture, nullptr, &rect);
}
