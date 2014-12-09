class sMenu : public Scene {
	UI *bg;
	UI *start;
	public:
		void init(){
			bg = BC(UI,Surface("menu/Background.jpg"));
			start = BC(UI,Surface("menu/Start.png"),bg,Vector2(0.5),Vector2(0.5),Vector2(0.1,0.1*GEK::screen.x/GEK::screen.y));
			on[eK_KEYDOWN] = [&](const eK_Event & e){
				switch(e.key.keysym.sym){
					case '\033':
							std::exit(0);
						break;
				};
			};
		}
		void loop(const double &deltatime){
			switch(GEK::mouse.status){
				case (Mouse::L):
					if(start->contains(GEK::mouse.position))
						GEK::scene = new sGame;
				default:break;
			}
			bg->draw();
			start->draw();
		};
};
