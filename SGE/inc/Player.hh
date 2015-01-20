#pragma once
#include <functional>
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
	char hp;
};
struct Private:Status {int secret=0;};

struct Player:Private {
	Vector2 direction;
	sockaddr_in address;
	char shooted;
	Player(int password = 0, char player_id = 0, char team_id = 0, sockaddr_in client_address = {0}, Vector2 initial_position = {0}, double initial_rotation = 0 ){
		id = player_id;
		team = team_id;
		score = 0;
		target = initial_position;
		position = initial_position;
		hp = 100;
		secret = password;
		direction = 0;
		rotation = initial_rotation;
		address = client_address;
		shoot = 0;
		shooted = 0;
	};
	void update(const Vector2 deltatime,const std::function<bool(const Vector2,const Vector2)>& check){
		direction = (target-position).unit();
		rotation = direction.angle();
		if((target-position).mag()>0.25){
			Vector2 new_position = position + direction*deltatime;
			if(check(new_position+Vector2(0.5),direction))
				position = new_position;
		}
	}
	void respawn(Vector2 new_position, double new_rotation){position=new_position;rotation=new_rotation;target=position;hp=100;}
	///Draws object in screen, using a map last camera render
	template<class T,cttc(T,TMX*)> void draw(Sprite* sprite,T &&map){sprite->draw(map->tracecast(position),rotation);}
};
