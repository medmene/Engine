#pragma once
#include "include/base_defs.h"

class TextManager
{
	TextManager();
public:
	static TextManager * instance();

	void Init(const string & res);
	u16string GetText(int id);
private:
	map<int, u16string>			m_strings;

	
	static TextManager * sm_instance;
};