#pragma once
#include <e2D.h>

class tSprite
{
	private:
		SDL_Texture *tex = 0;
		SDL_Rect dst;
		SDL_Renderer *ren;
	public:
		tSprite( const char *file, SDL_Renderer *renderer );
		tSprite( SDL_Texture *texture );
		tSprite &draw( int x = 0, int y = 0 );
		tSprite &drawarray(auto & CL);
};
