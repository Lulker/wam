class sGame : public Scene {
	private:
		TMX *map;
		Object *mc;
	public:
		void loop(const double &deltatime){
			switch(GEK::mouse.status){
				case (Mouse::L):
					mc->move(map->raycast(GEK::mouse.position));
					mc->aim();
				default:break;
			}
			mc->update(deltatime);
			map->camera(0, mc->position, GEK::screen/map->tile);
			mc->draw(map);
		};
		void init(){
			mc = BC(Object,BC(Sprite,Surface("gfx/character.png")),Vector2(10,10),5);
			map = BC(TMX,"maps/Map1.tmx",4);
			on[eK_KEYDOWN] = [&](const eK_Event & e){
				switch(e.key.keysym.sym){
					case '\033':
							std::exit(0);
						break;
				};
			};
		};
};
