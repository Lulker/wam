#pragma once
#include "Vector2.hh"
#include "Surface.hh"
#include "GEK.hh"

struct UI : public BCO {
	eK_Rect destination;
	eK_Texture *texture;
	~UI(){assert(true);SDL_DestroyTexture(texture);}
	static eK_Rect root(){return {0,0,(int)GEK->screen.x,(int)GEK->screen.y};}
	UI(const Surface &surface, eK_Rect parent = {0,0,(int)GEK->screen.x,(int)GEK->screen.y}, Vector2 EXT_ANCHOR = {0,0}, Vector2 INT_ANCHOR = {0,0}, Vector2 REL_SIZE = {1,1}){
		destination.x = parent.x + ((EXT_ANCHOR.x <= 1 && EXT_ANCHOR.x >= -1)?parent.w*EXT_ANCHOR.x:EXT_ANCHOR.x);
		destination.y = parent.y + ((EXT_ANCHOR.y <= 1 && EXT_ANCHOR.y >= -1)?parent.h*EXT_ANCHOR.y:EXT_ANCHOR.y);
		texture = assert(SDL_CreateTextureFromSurface(GEK->renderer, surface.surface));
		SDL_QueryTexture(texture, 0, 0, &destination.w, &destination.h);
		if(REL_SIZE.x<=1)
			destination.w = parent.w*REL_SIZE.x;
		if(REL_SIZE.y<=1)
			destination.h = parent.h*REL_SIZE.y;
		destination.x -= destination.w*(INT_ANCHOR.x);
		destination.y -= destination.h*(INT_ANCHOR.y);
	}
	UI(const Surface &surface, UI* parent, Vector2 EXT_ANCHOR = {0,0}, Vector2 INT_ANCHOR = {0,0}, Vector2 REL_SIZE = {1,1}):UI(surface,parent->destination,EXT_ANCHOR,INT_ANCHOR,REL_SIZE){};
	void draw(){SDL_RenderCopyEx(GEK->renderer, texture, 0, &destination, 0, 0, 0);}
	bool contains(const Vector2& position){ return (position.x > destination.x && position.y > destination.y && position.y < (destination.y+destination.h) && position.x < (destination.x+destination.w));}
};
