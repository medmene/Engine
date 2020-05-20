#pragma once
#include "base_defs.h"

using std::stringstream;
using std::ostringstream;

namespace Utils 
{
	inline vector<string> split(const string& str, const string& delim)
	{
		vector<string> out;
		std::size_t current, previous = 0;
		current = str.find(delim);
		while (current != std::string::npos) 
		{
			out.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find(delim, previous);
		}
		out.push_back(str.substr(previous, current - previous));
		return out;
	}
	inline vector<string> split(const string& str, char delim)
	{
		return split(str, std::to_string(delim));
	}
	
	inline vector<wstring> split(const wstring & str, const wstring & delim)
	{
		vector<wstring> out;
		std::size_t current, previous = 0;
		current = str.find(delim);
		while (current != std::string::npos)
		{
			out.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find(delim, previous);
		}
		out.push_back(str.substr(previous, current - previous));
		return out;
	}
	inline vector<wstring> split(const wstring & str, wchar_t delim)
	{
		return split(str, std::to_wstring(delim));
	}
	inline vector<u16string> split(const u16string & str, char16_t delim)
	{
		vector<u16string> out;
		std::size_t current, previous = 0;
		current = str.find(delim);
		while (current != std::string::npos)
		{
			out.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find(delim, previous);
		}
		out.push_back(str.substr(previous, current - previous));
		return out;
	}
	inline vector<u16string> split(const u16string & str, const u16string & delim)
	{
		vector<u16string> out;
		std::size_t current, previous = 0;
		current = str.find(delim);
		while (current != std::string::npos)
		{
			out.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find(delim, previous);
		}
		out.push_back(str.substr(previous, current - previous));
		return out;
	}
}