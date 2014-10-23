#include <eK.h>
#include <cmwc.h>
#include <ctime>

#define rand prng->rand

std::vector<tSprite*> sprites;
tTMX * map;
cmwc * prng;

//Character variables for the position and movement
int x_cell = 0;
int y_cell = 0;

void draw(eK & ge)
{
	map->draw(0, x_cell, ge.width/64+1+x_cell, y_cell, ge.height/64+1+y_cell, -ge.width%64+32, -ge.height%64+32);
	sprites[0]->draw( ge.width/2-32, ge.height/2-32 );
};

void init(eK & ge)
{
	sprites.reserve(100);
	sprites[0] = ge.sprite("gfx/character.bmp");
	map = ge.tmx("maps/Map1.tmx",4);
	ge.on[SDL_QUIT] = [](eK & ge,SDL_Event & e){exit(0);};
	ge.on[SDL_KEYDOWN] = [](eK & ge,SDL_Event & e){
		switch(e.key.keysym.sym){
			case SDLK_s:
			if(y_cell < 94)
					y_cell++;
				break;
			case SDLK_w:
			if (y_cell > -5)
					y_cell--;
				break;
			case SDLK_d:
			if(x_cell > 95)
					x_cell++;
				break;
			case SDLK_a:
			if(x_cell < -4)
					x_cell--;
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
