#include "include/game_object/TextBubble.h"
#include "include/input/Camera.h"
#include "include/controller/Animator.h"
#include "pugixml/pugixml.hpp"
#include "include/game_object/Label.h"
#include "include/tools/Utils.h"



TextBubble::TextBubble(const string & name)
	: GameObject(name)
	, m_defaultOffset(Vector2::zero)
	, m_textCenterPos(Vector2::zero)
	, m_fontSize(16)
{
}

TextBubble::~TextBubble()
{
	DestroyLabels();
}

void TextBubble::LoadGraphics(pugi::xml_node * node)
{
	GameObject::LoadGraphics(node);

	// Setup relative parent position
	if (!node->attribute("bubble_offset").empty())
	{
		auto tokens = utils::split(node->attribute("bubble_offset").value(), " ");
		m_defaultOffset.x = std::stoi(tokens[0]);
		m_defaultOffset.y = std::stoi(tokens[1]);
	}

	// Setup relative center of text position
	if (!node->attribute("text_offset").empty())
	{
		auto tokens = utils::split(node->attribute("text_offset").value(), " ");
		m_textCenterPos.x = std::stoi(tokens[0]);
		m_textCenterPos.y = std::stoi(tokens[1]);
	}

	// Setup relative center of text position
	if (!node->attribute("text").empty())
	{
		string value = node->attribute("text").value();
		m_text = u16string(value.begin(), value.end());
	}
}

void TextBubble::SetSide(BubbleSide s)
{
	if (m_currentSide != s)
	{
		m_currentSide = s;
		auto pos = GetRelativePos();
		switch (m_currentSide)
		{
		case LEFT:
			pos.x = -m_defaultOffset.x;
			pos.y = -m_defaultOffset.y;
			break;
		case RIGHT:
			pos.x = m_defaultOffset.x;
			pos.y = -m_defaultOffset.y;
			break;
		}
		UpdateRelativePos(pos);
	}
}

void TextBubble::SetText(const u16string& text)
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
			vector<u16string> elems = utils::split(m_text, u" ");
			
			int index = 0;
			vector<u16string> labels;
			labels.emplace_back(u"");
			
			while (index < elems.size())
			{
				if ((labels.back() + elems[index]).size() + 1 < maxSymbolsInRow)
				{
					labels.back() += elems[index];
					labels.back() += u" ";
				}
				else
				{
					index--;
					labels.emplace_back(u"");
				}
				index++;
			}

			// Add to labels
			for (int i = 0, j = 0; i < maxRows && j < labels.size(); ++i, ++j)
			{
				m_labels.emplace_back(new Label("label_" + std::to_string(i)));
				m_labels.back()->LoadSettings("times.ttf");
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
			m_labels.emplace_back(new Label("label_default"));
			m_labels.back()->LoadSettings("times.ttf");
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

		if (!m_staticObject)
		{
			// Apply zoom
			localRect.x *= Camera::instance()->GetZoom();
			localRect.y *= Camera::instance()->GetZoom();
			localRect.w *= Camera::instance()->GetZoom();
			localRect.h *= Camera::instance()->GetZoom();

			// Apply camera moving
			auto diff = Camera::instance()->GetDiff();
			localRect.x = localRect.x + diff.x;
			localRect.y = localRect.y + diff.y;
		}
		
		m_animator->GetActiveAnimation()->SetState(m_currentSide);
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
