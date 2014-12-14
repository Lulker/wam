class sGame : public Scene {
	private:
		TMX *map;
		Object *mc;
	public:
		void loop(const double &deltatime){
			mc->update(deltatime);
			if((*map)(1,mc->position.x,mc->position.y)!=-1)
				mc->update(-deltatime);
			map->camera(0, mc->position, GEK::screen/map->tile);
			mc->draw(map);
			map->camera(1, mc->position, GEK::screen/map->tile);
			switch(GEK::mouse.status){
				case (Mouse::L):
					mc->move(map->raycast(GEK::mouse.position));
					mc->aim();
					break;
				case (Mouse::R):
					mc->aim(map->raycast(GEK::mouse.position));
					SDL_RenderDrawLine(
						GEK::renderer,
						map->tracecast(mc->position+0.5).x,
						map->tracecast(mc->position+0.5).y,
						map->tracecast(mc->position+0.5).x+mc->direction.x*100,
						map->tracecast(mc->position+0.5).y+mc->direction.y*100);
				default:break;
			}
		};
		void init(){
			mc = BC(Object,BC(Sprite,Surface("gfx/character.png")),Vector2(10,12),5);
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
