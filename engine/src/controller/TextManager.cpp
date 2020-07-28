#include "include/controller/TextManager.h"


TextManager * TextManager::sm_instance = nullptr;

TextManager::TextManager()
{
	
}

TextManager* TextManager::instance()
{
	if (!sm_instance)
	{
		sm_instance = new TextManager();
	}
	return sm_instance;
}

void TextManager::Init(const string& res)
{
}

u16string TextManager::GetText(int id)
{
	return m_strings[id];
}
