#pragma once
#include <eK.hpp>

class sGame : public tScene
{
	private:
		tTMX *map;
		tObject *mc;
	public:
	void quit(){
		delete map;
	};
	void loop(){
		map->camera(0, 1, mc->x,mc->y,(long)(ek->width/(2*64))+2,(long)(ek->height/(2*64))+2);
		mc->update()->draw(map);
	};
	void init(){
		mc = ek->sprite("gfx/character.png")->object(10,10,2);
		map = ek->tmx("maps/Map1.tmx",4);
		on[SDL_MOUSEBUTTONDOWN] = [this](SDL_Event& e){
			if(e.button.type == SDL_MOUSEBUTTONDOWN)
				switch(e.button.button){
					case SDL_BUTTON_LEFT:
						mc->move(map->xraycast(e.button.x),map->yraycast(e.button.y))->aim();
						break;
				}
		};
		on[SDL_KEYDOWN] = [this](SDL_Event & e){
			switch(e.key.keysym.sym){
				case SDLK_ESCAPE:
						ek->exit(0);
					break;
			};
		};
	};
};
