#include <eK.hpp>
#include <cmwc.h>
#include <ctime>

std::vector<tSprite*> sprites;
tTMX * map;
cmwc * prng;

//Character variables for the position and movement (to be moved to character class)
float x_cell = 10;
float y_cell = 10;

void draw(eK & ge)
{
	map->camera(0, 1, x_cell,y_cell,(long)(ge.width/(2*64))+1,(long)(ge.height/(2*64))+1);
	sprites[0]->draw( ge.width/2, ge.height/2 );
};

void init(eK & ge)
{
	sprites.reserve(100);
	sprites[0] = ge.sprite("gfx/character.png");
	map = ge.tmx("maps/Map1.tmx",4);
	ge.on[SDL_KEYDOWN] = [](eK & ge,SDL_Event & e){
		switch(e.key.keysym.sym){
			case SDLK_s:
					y_cell+=(float)1/64;
				break;
			case SDLK_w:
					y_cell-=(float)1/64;
				break;
			case SDLK_d:
					x_cell+=(float)1/64;
				break;
			case SDLK_a:
					x_cell-=(float)1/64;
				break;
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

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	std::string name(GetCommandLine());
	const char * program = &name[0] + 1 + name.find_last_of("\\");
#else
int main(int argc, char const *argv[])
{
	std::string name = argv[0];
	const char * program = &name[0];
#endif
	*(&name[0] + name.find_last_of(".")) = 0;
	prng = new cmwc(time(0));
	return eK(program).init(init).loop(draw);
}
