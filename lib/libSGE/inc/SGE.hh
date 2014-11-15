#pragma once
#ifdef _WIN32
	#include <winsock2.h>
	#include <windows.h>
#else
	#include <arpa/inet.h>
#endif

#define M_PI  3.14159265358979323846264338327950288419716939937510
#include <cmath>
#include <string>
#include <cstdint>
#include <uSDL.hh>
#include <unistd.h>
#include <algorithm>
#include <functional>
#include <Meta.hh>

#define SGE_Main(scene) IF_WIN(int WinMain(HINSTANCE, HINSTANCE, LPSTR, int),int main(int argc, char const *argv[])){\
	std::string name(IF_WIN(GetCommandLine(),argv[0]));\
	const char *title = &name[0] + 1 + name.find_last_of(IF_WIN("\\","/"));\
	*(&name[0] + name.find_last_of(".")) = 0;\
	chdir(&name[0]);\
	return SGE::GEK::main(title,scene);\
}

namespace SGE{
	#include <Vector2.hh>
	#include <Scene.hh>
	#include <GEK.hh>
	#include <Surface.hh>
	#include <Sprite.hh>
	#include <TMX.hh>
	#include <Object.hh>
	#include <CMWC.hh>
}
