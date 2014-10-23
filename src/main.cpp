#include <eK.h>
#include <cmwc.h>
#include <ctime>

#define rand prng->rand

std::vector<tSprite*> sprites;
tTMX * map;
cmwc * prng;

//Character variables for the position and movement
int x_pos = 0;
int y_pos = 0;
int c_speed = 64;

void draw(eK & ge)
{
	map->draw(0, 0, 99, 0, 99, 0, 0);
	sprites[0]->draw( x_pos, y_pos );
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
					y_pos = y_pos + c_speed;
				break;
			case SDLK_w:
					y_pos = y_pos - c_speed;
				break;
			case SDLK_d:
					x_pos = x_pos + c_speed;
				break;
			case SDLK_a:
					x_pos = x_pos - c_speed;
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
