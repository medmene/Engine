#pragma once
#include "include/base_defs.h"

using std::stringstream;
using std::ostringstream;

namespace utils {
	inline vector<string> split(const string& str, const string& delim) {
		vector<string> out;
		std::size_t current, previous = 0;
		current = str.find(delim);
		while (current != std::string::npos) {
			out.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find(delim, previous);
		}
		out.push_back(str.substr(previous, current - previous));
		return out;
	}

	inline vector<u16string> split(const u16string & str, const u16string & delim) {
		vector<u16string> out;
		std::size_t current, previous = 0;
		current = str.find(delim);
		while (current != std::string::npos) {
			out.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find(delim, previous);
		}
		out.push_back(str.substr(previous, current - previous));
		return out;
	}

	template <class T>
	inline void unique_add(vector<T> & out, const T & elem) {
		if (std::find(out.begin(), out.end(), elem) == out.end()) {
			out.emplace_back(elem);
		}
	}
}