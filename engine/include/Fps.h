#pragma once
#include <chrono>
#include "Core.h"

class _FPS
{
public:
	_FPS()
	{
		t_start = std::chrono::high_resolution_clock::now();
	}
	void UpdateFPS()
	{
		auto t_end = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<double, std::milli>(t_end - t_start).count();
		std::ostringstream _s;
		_s << (60 / dt);
		fps = "FPS - " + _s.str();
		std::ostringstream _s2;
		_s2 << (dt);
		fps += "\tdt: " + _s2.str();
		t_start = std::chrono::high_resolution_clock::now();
	}

	string													fps;
	double													dt;
private:
	std::chrono::time_point<std::chrono::steady_clock>		t_start;
};