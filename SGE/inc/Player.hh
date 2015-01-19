#pragma once
#include "Sprite.hh"
#include "TMX.hh"
#include "UDP.hh"

struct Status {
	char id;
	char team;
	char score;
	Vector2 target;
	double rotation;
	Vector2 position;
	char shoot;
};

struct Private:Status {int hp,secret = 0;};

struct Player:Private {
	///Draws object in screen, using a map last camera render
	template<class T,cttc(T,TMX*)> void draw(Sprite* sprite,T &&map){sprite->draw(map->tracecast(position),rotation);}
};
