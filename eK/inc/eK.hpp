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
class tSprite;
class tObject;

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
		std::chrono::steady_clock::time_point move_timestamp;
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
		void move(int x, int y);
		/**
		* Draws object in a map, using that map last camera render
		* @param map a pointer to the map
		**/
		void draw(tTMX *map);
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
		/**
		* Draws sprite in a position of the screen
		* @param x horizontal position in screen
		* @param y vertical position in screen
		**/
		void draw(int x = 0, int y = 0);
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
		tTMX(const char *file, eK &ek, const int &offset);
		float xo;
		float yo;
	public:
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
		SDL_Window *win = 0;
		SDL_Renderer *ren = 0;
		const char *name;
	public:
		///Contiene el tamaño vertical de la pantalla
		int height;
		///Contiene el tamaño horizontal de la pantalla
		int width;
		/**
		* Hash map que contiene los diferentes eventos, preparado para tiempo de acceso O(1)
		* cada evento es identificado por un int (correspondiente al evento SDL) y contiene
		* una función void que recibe como parámetros el motor y el evento.
		**/
		std::unordered_map<int,std::function<void(eK&,SDL_Event&)>> on;
		/**
		* Inicializa motor (librerías sdl)
		* @param title El título de la ventana
		**/
		eK(const char *title);
		~eK();
		/**
		* Inicializa los valores por defecto del motor y ejecuta una función definida por el usuario "init"
		* @param init función que recibe como parámetro el motor
		* @return el motor en si
		**/
		eK &init(void(*init)(eK&));
		/**
		* Starts game loop
		* @param draw function that is iterated forever
		**/
		int loop(void(*draw)(eK&));
		/**
		* Sets background color
		* @param r red
		* @param g green
		* @param b blue
		**/
		void bg(const int &&r, const int &&g, const int &&b);
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
