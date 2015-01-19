#pragma once
#include "Scene.hh"
#include "Vector2.hh"
#include "Surface.hh"

struct Mouse {
	enum Button {NONE,L,M,LM,R,LR,RM,ANY} status;
	Button updated;
	Vector2 position;
};

#define aspectratio GEK::screen.x/GEK::screen.y

struct GEK {
	static void clean();
	static const char *server;
	static eK_Window *window;
	static eK_Renderer *renderer;
	///Scene that will run
	static Scene *scene;
	///Contains screen size
	static Vector2 screen;
	///Contains mouse position
	static Mouse mouse;
	///Returns a text as a texture
	static Surface text(const char *str);
	///Sets background color
	static void bg(const int &red, const int &green, const int &blue){SDL_SetRenderDrawColor(renderer, red, green, blue, 255);};
	///Scene manager
	static int main(const char*, Scene*);
};
