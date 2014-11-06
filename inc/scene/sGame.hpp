class sGame : public Scene
{
	private:
		TMX *map;
		Object *mc;
		Object *mc2;
	public:
	void quit(){
		delete map;
		delete mc;
		delete mc2;
		delete this;
	};
	void loop(const double &deltatime){
		map->camera({0,1}, mc->position,Vector2<double>(GEK::screen)/=128);
		mc->update(deltatime);
		mc->draw(map);
	};
	void init(){
		mc = new Object(new Sprite(Surface("gfx/character.png")),10,10,2);
		map = new TMX("maps/Map1.tmx",4);
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
