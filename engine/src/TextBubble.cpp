#include "include/TextBubble.h"
#include "include/Camera.h"
#include "include/Animator.h"
#include "pugixml/pugixml.hpp"
#include "include/Label.h"


TextBubble::TextBubble(SDL_Renderer* renderer, const string& src, ResourceManager::Type type)
	: GameObject(renderer, src, type)
	, m_defaultRelPos(Vector2::zero)
	, m_fontSize(16)
{
	m_currentSide = RIGHT;

	if (m_resourceSettings)
	{
		pugi::xml_document doc;
		doc.load_file(m_resourceSettings->GetPath().c_str());
		auto rootNode = doc.child("object");

		auto relNode = rootNode.child("relativePos");
		int x = std::stoi(relNode.attribute("x").value());
		int y =  std::stoi(relNode.attribute("y").value());
		m_defaultRelPos = Vector2(x, y);

		auto defTextNode = rootNode.child("textCenterRelPos");
		x = std::stoi(defTextNode.attribute("x").value());
		y = std::stoi(defTextNode.attribute("y").value());
		m_textCenterPos = Vector2(x, y);
	}
}

TextBubble::~TextBubble()
{
	DestroyLabels();
}

void TextBubble::SetSide(Side s)
{
	if (m_currentSide != s)
	{
		m_currentSide = s;
		auto pos = GetRelativePos();
		switch (m_currentSide)
		{
		case LEFT:
			pos.x = -m_defaultRelPos.x;
			pos.y = -m_defaultRelPos.y;
			break;
		case RIGHT:
			pos.x = m_defaultRelPos.x;
			pos.y = -m_defaultRelPos.y;
			break;
		}
		UpdateRelativePos(pos);
	}
}

void TextBubble::SetText(const string& text)
{
	if (!text.empty())
	{
		m_text = text;
		DestroyLabels();
		
		int maxSymbolsInRow = (int)(m_size.x * 0.95f) / (m_fontSize * 0.5f);
		int maxRows = (int)(m_size.y * 0.85f) / m_fontSize;
		
		if (m_text.size() > maxSymbolsInRow)
		{
			// Split
			vector<string> elems;
			std::stringstream ss(m_text + ' ');
			string item;
			
			while (getline(ss, item, ' '))
			{
				elems.emplace_back(item);
			}
			
			int index = 0;
			vector<string> labels;
			labels.emplace_back("");
			
			while (index < elems.size())
			{
				if ((labels.back() + elems[index]).size() + 1 < maxSymbolsInRow)
				{
					labels.back() += elems[index];
					labels.back() += " ";
				}
				else
				{
					index--;
					labels.emplace_back("");
				}
				index++;
			}

			// Add to labels
			for (int i = 0, j = 0; i < maxRows && j < labels.size(); ++i, ++j)
			{
				m_labels.emplace_back(new Label(m_renderer, "times", ResourceManager::TTF));
				m_labels.back()->SetParent(this);
				m_labels.back()->Init(labels[j], m_fontSize);
				m_labels.back()->SetVisible(true);
				m_labels.back()->SetFollowVisibility(true);
			}

			Color clr = Color(0, 0, 0, 255);
			// Update positions
			for (int i = 0; i < m_labels.size(); ++i)
			{
				int middle = m_labels.size() / 2;
				int posY = (i - middle) * m_fontSize;
				posY += (m_labels.size() % 2 == 0 ? 10 : 0);
				m_labels[i]->UpdateRelativePos(Vector2(0, posY)+ m_textCenterPos);
				m_labels[i]->UpdateColor(clr);
			}
		}
		else
		{
			m_labels.emplace_back(new Label(m_renderer, "times", ResourceManager::TTF));
			m_labels.back()->Init(m_text, m_fontSize);
			m_labels.back()->SetParent(this);
			m_labels.back()->SetVisible(true);
			m_labels.back()->SetFollowVisibility(true);
			m_labels.back()->UpdateRelativePos(m_textCenterPos);
			m_labels.back()->UpdateColor(Color(0, 0, 0, 255));
		}
	}
}

void TextBubble::Update(float dt)
{
	GameObject::Update(dt);
	
	for (auto && lbl : m_labels)
	{
		lbl->Update(dt);
	}
}

void TextBubble::Render()
{
	if (IsVisible())
	{
		SDL_Rect localRect = m_rect;

		// Apply camera moving
		if (!m_staticObject)
		{
			auto diff = Camera::instance()->GetDiff();
			localRect.x = localRect.x + diff.x;
			localRect.y = localRect.y + diff.y;
		}

		// Apply zoom
		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		switch (m_currentSide)
		{
		case LEFT:
			m_animator->GetActiveAnimation()->SetState(1);
			break;
		case RIGHT:
			m_animator->GetActiveAnimation()->SetState(0);
			break;
		}

		// SDL_Rect a = m_animator->GetActiveAnimation()->GetCurrentState();
		SDL_RenderCopy(m_renderer, m_texture, &m_animator->GetActiveAnimation()->GetCurrentState(), &localRect);
	}
	
	for (auto && lbl : m_labels)
	{
		lbl->Render();
	}
}

void TextBubble::DestroyLabels()
{
	for (auto && lbl : m_labels)
	{
		delete lbl;
	}
	m_labels.clear();
}
