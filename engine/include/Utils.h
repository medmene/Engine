#pragma once
#include "Core.h"

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
}