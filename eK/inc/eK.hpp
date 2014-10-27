#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include <SDL.h>
#include <assert.h>
#include <eDBG.h>

class eK;
class tTMX;
class tSprite;

class tSprite {
	friend class eK;
	private:
		SDL_Texture *tex = 0;
		SDL_Rect dst;
		SDL_Renderer *ren;
		tSprite(const char *file, SDL_Renderer *renderer);
	public:
		/**
		* Dibuja el sprite en la posición x, y de la pantalla
		* @param x posición en el eje de las x
		* @param y posición en el eje de las y
		**/
		void draw(int x = 0, int y = 0);
};

class tTMX {
	friend class eK;
	private:
		std::vector<tSprite*> tileset;
		std::vector<int*> layers;
		tTMX(const char *file, eK &ek, const int &offset);
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
		* Empieza el loop principal del juego
		* @param draw función que recibe como parámetro el motor
		* @return un entero correspondiente al valor de salida del loop
		**/
		int loop(void(*draw)(eK&));
		/**
		* Cambia el color en el que se pintará el fondo
		* @param r red
		* @param g green
		* @param b blue
		**/
		void bg(const int &&r, const int &&g, const int &&b);
		/**
		* Carga una imágen como sprite
		* @param file el nombre del archivo a cargar
		* @return un puntero al sprite en cuestión
		**/
		tSprite *sprite(const char *file);
		/**
		* Carga el mapa de un archivo
		* @param file el nombre del archivo a cargar
		* @param offset número de carácteres a ignorar en el path de los sprites
		* @return un puntero al mapa en cuestión
		**/
		tTMX *tmx(const char *file, const int &offset);
};
