#pragma once
#include <unordered_map>
#include <functional>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <tSprite.h>
#include <tFont.h>
#include <assert.h>

class eK
{
	private:
		SDL_Window *win = 0;
		SDL_Renderer *ren = 0;
		const char *name;
	public:
		std::unordered_map<int,std::function<void(eK&,SDL_Event&)>> on;
		eK( const char *title );
		~eK();
		int loop( void(*draw)(eK&) );
		eK &init( void(*init)(eK&) );
		eK &bg( const int &&r, const int &&g, const int &&b );
		tSprite *sprite(const char* file);
};
