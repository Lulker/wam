#include <eK.hpp>
#include <cmwc.h>
#include <ctime>

std::vector<tSprite*> sprites;
tTMX * map;
cmwc * prng;

//Character variables for the position and movement (to be moved to character class)
tObject * mc;

void draw(eK & ge){
	map->camera(0, 1, mc->cx,mc->cy,(long)(ge.width/(2*64))+1,(long)(ge.height/(2*64))+1);
	mc->update()->draw(map);
};

void init(eK & ge){
	mc = ge.sprite("gfx/character.png")->object(10,10,2);
	map = ge.tmx("maps/Map1.tmx",4);
	ge.on[SDL_MOUSEBUTTONDOWN] = [](eK& ge,SDL_Event& e){
		if(e.button.type == SDL_MOUSEBUTTONDOWN)
			switch(e.button.button){
				case SDL_BUTTON_LEFT:
					mc->move(map->xraycast(e.button.x),map->yraycast(e.button.y))->aim();
					break;
			}
	};
	ge.on[SDL_KEYDOWN] = [](eK & ge,SDL_Event & e){
		switch(e.key.keysym.sym){
			case SDLK_ESCAPE:
					exit(0);
				break;
		};
	};
/*
	ge.on[SDL_KEYUP] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEMOTION] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEBUTTONDOWN] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEBUTTONUP] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_DROPFILE] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_MOUSEWHEEL] = [](eK& ge,SDL_Event& e){exit(0);};
	ge.on[SDL_DROPFILE] = [](eK& ge,SDL_Event& e){exit(0);};
*/
};

#ifdef __WIN32
#include <windows.h>

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	std::string name(GetCommandLine());
	const char * program = &name[0] + 1 + name.find_last_of("\\");
#else
int main(int argc, char const *argv[]){
	std::string name = argv[0];
	const char * program = &name[0];
#endif
	*(&name[0] + name.find_last_of(".")) = 0;
	prng = new cmwc(time(0));
	return eK(program).init(init).loop(draw);
}
