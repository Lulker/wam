class sStart : public Scene {
	Sprite *bg;
	Sprite *start;
	public:
		void init(){
			bg = BC(Sprite,Surface("menu/Background.jpg"));
			start = BC(Sprite,Surface("menu/Start.png"));
		}
		void loop(const double &deltatime){
			switch(GEK::mouse.status){
				case (Mouse::L):
					if(GEK::mouse.position.clamp(GEK::screen/2,(GEK::screen/2)+256) == GEK::mouse.position)
						GEK::scene = new sGame;
				default:break;
			}
			bg->draw({0, 0});
			start->draw(GEK::screen/2);
		};
};
