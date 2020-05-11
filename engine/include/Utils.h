#pragma once
#include "base_defs.h"

using std::stringstream;
using std::ostringstream;

namespace Utils 
{
	inline vector<string> split(const string & _src, char _delilm)
	{
		vector<string> elems;
		stringstream ss(_src + ' ');
		string item;
		while (getline(ss, item, _delilm))
		{
			elems.emplace_back(item);
		}
		return elems;
	}
	inline vector<wstring> split(const wstring & _src, wchar_t _delilm)
	{
		vector<wstring> elems;
		std::wstringstream ss(_src + L' ');
		wstring item;
		while (getline(ss, item, _delilm))
		{
			elems.emplace_back(item);
		}
		return elems;
	}
	inline vector<u16string> split(const u16string & _src, char16_t _delilm)
	{
		vector<u16string> elems;
		std::basic_stringstream<char16_t> ss(_src + u' ');
		u16string item;
		while (getline(ss, item, _delilm))
		{
			elems.emplace_back(item);
		}
		return elems;
	}
}