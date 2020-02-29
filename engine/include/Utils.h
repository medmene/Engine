#pragma once
#include "Core.h"
#include "Vector2.h"
#include "Vector3.h"

using std::stringstream;
using std::ostringstream;

namespace Utils 
{
	const vector<string> split(const string & _src, char _delilm)
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

namespace Converter
{
	template <typename T>
	const string convert_template(T _num)
	{
		ostringstream _stream;
		_stream << _num;
		return _stream.str();
	}
	const string convert(int _elem) {
		ostringstream _stream;
		_stream << _elem;
		return _stream.str();
	}
	const string convert(float _elem) {
		ostringstream _stream;
		_stream << _elem;
		return _stream.str();
	}
	const string convert(double _elem) {
		ostringstream _stream;
		_stream << _elem;
		return _stream.str();
	}
	const string convert(bool _elem) {
		ostringstream _stream;
		_stream << _elem;
		return _stream.str();
	}
	const string convert(unsigned int _elem) {
		ostringstream _stream;
		_stream << _elem;
		return _stream.str();
	}
	const string convert(long _elem) {
		ostringstream _stream;
		_stream << _elem;
		return _stream.str();
	}
	const string convert(long long _elem) {
		ostringstream _stream;
		_stream << _elem;
		return _stream.str();
	}
	const string convert(const Vector2 & _elem) {
		string result = "(";
		result += convert(_elem.x);
		result += ";";
		result += convert(_elem.y);
		result += ")";
		return result;
	}
	const string convert(const Vector3 & _elem) {
		string result = "(";
		result += convert(_elem.x);
		result += ";";
		result += convert(_elem.y);
		result += ";";
		result += convert(_elem.z);
		result += ")";
		return result;
	}
}
