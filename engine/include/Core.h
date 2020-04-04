#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <locale>
#include <conio.h>
#include <cstdio>
#include <filesystem>
#include <thread>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

//#pragma comment(lib,"SDL/SDL2.lib")
//#pragma comment(lib,"SDL/SDL2main.lib")
//#pragma comment(lib,"SDL/SDL2_image.lib")
//#pragma comment(lib,"SDL/SDL2_ttf.lib")

#undef main
#define endl "\n"

using std::string;
using std::vector;
using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::find;
using std::wstring;