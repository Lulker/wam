#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include <chrono>
#include <SDL.h>
#include <assert.h>
#include <eDBG.h>

class eK;
class tTMX;
class tScene;
class tSprite;
class tObject;

extern "C" void eKmain();

///Global variable containing game engine
extern eK *game_engine;

class tScene {
	public:
		eK *&ek = game_engine;
		/**
		* Hash map that contains functions for the different events
		* every event is identified by an int (corresponds to SDL event)
		* and contains a void function that gets event as parameter
		**/
		std::unordered_map<int,std::function<void(SDL_Event&)>> on;
		///Function executed when scene starts
		virtual void init()=0;
		///Function executed every frame while scene lasts
		virtual void loop()=0;
		///Function executed when scene ends
		virtual void quit()=0;
};

class tObject {
	friend class tSprite;
	private:
		tSprite *s;
		float x0;
		float y0;
		float Ax;
		float Ay;
		float Axy;
		float ms;
		float rot = 0;
		std::chrono::steady_clock::time_point move_timestamp;
	protected:
		tObject(tSprite *sprite, float x, float y, float speed);
	public:
		///Current X position
		float cx;
		///Current Y position
		float cy;
		/**
		* Starts moving object to target position
		* @param x horizontal position in map
		* @param y vertical position in map
		**/
		tObject *move(int x, int y);
		/**
		* Draws object in a map, using that map last camera render
		* @param map a pointer to the map
		**/
		tObject *draw(tTMX *map);
		///Aims in the direction the object is going to move
		tObject *aim();
		///Updates the object state/position
		tObject *update();
};

class tSprite {
	friend class eK;
	private:
		SDL_Texture *tex;
		SDL_Rect dst;
		SDL_Renderer *ren;
		tSprite(const char *file, SDL_Renderer *renderer);
	public:
		~tSprite();
		/**
		* Draws sprite in a position of the screen
		* @param x horizontal position in screen
		* @param y vertical position in screen
		* @param angle optional angle to rotate sprite
		**/
		void draw(int x = 0, int y = 0, float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
		/**
		* Creates an object
		* @param x horizontal position in map
		* @param y vertical position in map
		* @param speed optional parameter to set object move speed in tiles per second
		**/
		tObject *object(float x, float y, float speed = 0);
};

class tTMX {
	friend class eK;
	private:
		std::vector<tSprite*> tileset;
		std::vector<int*> layers;
		float xo;
		float yo;
		tTMX(const char *file, eK &ek, const int &offset);
	public:
		~tTMX();
		///Map tile width
		int tilewidth;
		///Map tile height
		int tileheight;
		///Total map width
		int width;
		///Total map height
		int height;
		/**
		* Renders map in screen
		* @param layer0 the first layer to start drawing from
		* @param layer the last layer to draw
		* @param x horizontal position in map
		* @param y vertical position in map
		* @param Ax horizontal radius of sight
		* @param Ay vertical radius of sight
		**/
		void camera(int layer0, int layer, float x, float y, int Ax, int Ay);
		/**
		* Gets x map position from screen position
		* @param x position in screen
		* @return x position in map
		**/
		float xraycast(const int &x);
		/**
		* Gets y map position from screen position
		* @param y position in screen
		* @return y position in map
		**/
		float yraycast(const int &y);
		/**
		* Gets x screen position from map position
		* @param x position in map
		* @return x position in screen
		**/
		float xtracecast(const float &x);
		/**
		* Gets y screen position from map position
		* @param y position in map
		* @return y position in screen
		**/
		float ytracecast(const float &y);
};

class eK {
	private:
		#ifdef __WIN32
		friend int ::WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
		#else
		friend int ::main(int argc, char const *argv[]);
		#endif
		eK(const char *title);
		SDL_Renderer *ren = 0;
		SDL_Window *win = 0;
		int ret = 0;
		int main();
		~eK();
	public:
		///Contains screen height
		int height;
		///Contains screen width
		int width;
		///Scene that will run
		tScene *scene;
		/**
		* Exists the game
		* @param code exit code
		*/
		void exit(const int &code);
		/**
		* Sets background color
		* @param r red
		* @param g green
		* @param b blue
		**/
		void bg(const int &r, const int &g, const int &b);
		/**
		* Loads sprite from a file
		* @param file name of the sprite file to load
		* @return pointer to the created sprite
		**/
		tSprite *sprite(const char *file);
		/**
		* Loads map from a file
		* @param file name of the map file to load
		* @param offset number of characters to ignore in sprite path
		* @return pointer to the map sprite
		**/
		tTMX *tmx(const char *file, const int &offset);
};
