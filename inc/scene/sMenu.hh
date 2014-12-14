class sMenu : public Scene {
	enum elements {background,start,exit,start_hover,exit_hover};
	UI *menu[5];
	public:
		void init(){
			menu[background] = BC(UI,Surface("menu/Background.jpg"));
			menu[start] = BC(UI,Surface("menu/Start.png"),menu[0],Vector2(0.3,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
			menu[exit] = BC(UI,Surface("menu/Exit.png"),menu[0],Vector2(0.7,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
			menu[start_hover] = BC(UI,Surface("menu/Start_hover.png"),menu[0],Vector2(0.3,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
			menu[exit_hover] = BC(UI,Surface("menu/Exit_hover.png"),menu[0],Vector2(0.7,0.9),Vector2(0.5),Vector2(0.2,0.1*aspectratio));
		}
		void loop(const double &deltatime){
			for(int i=0;i<3;++i)
				menu[i]->draw();
			if(menu[start]->contains(GEK::mouse.position)){
				menu[start_hover]->draw();
				if(GEK::mouse.status && Mouse::L)
					GEK::scene = new sGame;
			} else if(menu[exit]->contains(GEK::mouse.position)){
				menu[exit_hover]->draw();
				if(GEK::mouse.status && Mouse::L)
					std::exit(0);
			}
		}
};
