class sGame : public Scene
{
	private:
		TMX *map;
		Object *mc;
	public:
		void loop(const double &deltatime){
			map->camera({0,1}, mc->position,GEK::screen()(div,map->tile));
			mc->update(deltatime);
			mc->draw(map);
		};
		void init(){
			Surface test("gfx/character.png");
			mc = BC<Object>(BC<Sprite>(test),10,10,2);
			map = BC<TMX>("maps/Map1.tmx",4);
			on[eK_MOUSEBUTTONDOWN] = [&](const eK_Event& e){
				if(e.button.type == eK_MOUSEBUTTONDOWN)
					switch(e.button.button){
						case eK_BUTTON_LEFT:
							mc->move(map->raycast(Vector2<>(e.button.x,e.button.y)));
							mc->aim();
							break;
					}
			};
			on[eK_KEYDOWN] = [&](const eK_Event & e){
				switch(e.key.keysym.sym){
					case '\033':
							std::exit(0);
						break;
				};
			};
		};
};
