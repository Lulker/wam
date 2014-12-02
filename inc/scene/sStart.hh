class sStart : public Scene {
	Object *bg;
	TMX *map;
	public:
		void init(){
			bg = BC(Object,BC(Sprite,Surface("menu/Background.jpg")),Vector2(0,0),2);
			map = BC(TMX,"maps/Map1.tmx",4);
		}
		void loop(const double &deltatime){
			switch(GEK::mouse.status){
				case (Mouse::L):
					GEK::scene = new sGame;
				default:break;
			}
			bg->update(deltatime);
			bg->draw(map);
		};
};
