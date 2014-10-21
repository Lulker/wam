#pragma once
#include <unordered_map>
#include <functional>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <tSprite.h>
#include <tFont.h>
#include <assert.h>

class e2D
{
	private:
		SDL_Window *win = 0;
		SDL_Renderer *ren = 0;
		const char *name;
	public:
		std::unordered_map<int,std::function<void(e2D&,SDL_Event&)>> on;
		e2D( const char *title );
		~e2D();
		int loop( void(*draw)(e2D&) );
		e2D &init( void(*init)(e2D&) );
		e2D &bg( const int &&r, const int &&g, const int &&b );
		tSprite *sprite(const char* file);
};
