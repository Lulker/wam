#pragma once
#include "Meta.hh"
#include "uSDL.hh"

class Surface : public BCO {
	public:
		eK_Surface *surface;
		///Loads image from path as surface
		Surface(const char *path):surface(assert(IMG_Load(path))){}
		Surface(eK_Surface *surface):surface(assert(surface)){}
		~Surface(){assert(true);SDL_FreeSurface(surface);}
};
