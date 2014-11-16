#pragma once
#ifdef _WIN32
	#include <winsock2.h>
	#include <windows.h>
	#include <direct.h>
	#define chdir(...) _chdir(__VA_ARGS__)
#else
	#include <arpa/inet.h>
	#include <unistd.h>
#endif

#define M_PI  3.14159265358979323846264338327950288419716939937510
#include <cmath>
#include <string>
#include <cstdint>
#include <uSDL.hh>
#include <algorithm>
#include <functional>
#include <Meta.hh>

namespace SGE{
	#include <Vector2.hh>
	#include <Scene.hh>
	#include <GEK.hh>
	#include <Surface.hh>
	#include <Sprite.hh>
	#include <TMX.hh>
	#include <Object.hh>
	#include <CMWC.hh>
	#include <UDP.hh>
}
