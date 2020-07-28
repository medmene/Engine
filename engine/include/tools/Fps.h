#pragma once
#include <chrono>
#include <stdio.h>
#include "include/Core.h"

class _FPS
{
public:
	_FPS()
		: dt(0.f)
	{
		t_start = std::chrono::high_resolution_clock::now();
	}
	void UpdateFPS()
	{
		auto t_end = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::milli>(t_end - t_start).count();
		char buf[30];
		sprintf(buf, "FPS - %.2f\tdt: %.2f", 60 / dt, dt);
		fps = buf;
		t_start = std::chrono::high_resolution_clock::now();
	}

	float													dt;
	string													fps;
private:
	std::chrono::time_point<std::chrono::steady_clock>		t_start;
};