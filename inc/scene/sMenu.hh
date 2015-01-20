#include <thread>
#include <chrono>
#include <UI.hh>
#include <Scene.hh>
#include "sGame.hh"
void server(const int);
struct sMenu : public Scene {
	enum elements {background,start,host,exit,start_hover,host_hover,exit_hover,menu_size};
	UI *menu[menu_size];
	sMenu(){
		menu[background] = BC(UI,Surface("menu/Background.jpg"));
		menu[start] = BC(UI,Surface("menu/Start.png"),menu[0],Vector2(0.2,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
		menu[host] = BC(UI,Surface("menu/Host.png"),menu[0],Vector2(0.5,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
		menu[exit] = BC(UI,Surface("menu/Exit.png"),menu[0],Vector2(0.8,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
		menu[start_hover] = BC(UI,Surface("menu/Start_hover.png"),menu[0],Vector2(0.2,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
		menu[host_hover] = BC(UI,Surface("menu/Host_hover.png"),menu[0],Vector2(0.5,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
		menu[exit_hover] = BC(UI,Surface("menu/Exit_hover.png"),menu[0],Vector2(0.8,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
	}
	Scene* operator()(){
		for(int i=0;i<4;++i)
			menu[i]->draw();
		if(menu[start]->contains(GEK->mouse.position)){
			menu[start_hover]->draw();
			if(GEK->mouse.status && Mouse::L)
				return new sGame;
		} else if(menu[host]->contains(GEK->mouse.position)){
			menu[host_hover]->draw();
			if(GEK->mouse.status && Mouse::L){
				std::thread(server,7331).detach();
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				return new sGame;
			}
		} else if(menu[exit]->contains(GEK->mouse.position)){
			menu[exit_hover]->draw();
			if(GEK->mouse.status && Mouse::L)
				return 0;
		}
		return this;
	}
};
