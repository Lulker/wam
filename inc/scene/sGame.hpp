using namespace SGE;

class sGame : public Scene
{
	private:
		TMX *map;
		Object *mc;
	public:
	void quit(){
		delete map;
		delete this;
	};
	void loop(const double &deltatime){
		map->camera(0, 1, mc->position,(Vector2<double>(0.5)*=GEK::screen));
		mc->update(deltatime);
		mc->draw(map);
	};
	void init(){
		mc = new Object(Sprite(Surface("gfx/character.png")),10,10,2);
		map = new TMX("maps/Map1.tmx",4);
		on[eK_MOUSEBUTTONDOWN] = [&](const eK_Event& e){
			if(e.button.type == eK_MOUSEBUTTONDOWN)
				switch(e.button.button){
					case eK_BUTTON_LEFT:
						mc->move(map->raycast(Vector2<double>(e.button.x,e.button.y)));
						mc->aim();
						break;
				}
		};
		on[eK_KEYDOWN] = [&](const eK_Event & e){
			switch(e.key.keysym.sym){
				case '\033':
						GEK::exit(0);
					break;
			};
		};
	};
};
