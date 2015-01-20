#include <Scene.hh>
#include <Player.hh>
#include <UI.hh>

struct sGame : public Scene {
	TMX* map;
	int id;
	Sprite* green;
	Sprite* red;
	Surface* hp_fill;
	UDP socket;
	sockaddr_in server;
	std::unordered_map<int,Player> players;
	sGame(){
		green = BC(Sprite,Surface("gfx/green.png"));
		red = BC(Sprite,Surface("gfx/red.png"));
		hp_fill = BC(Surface,"gfx/hp_fill.png");
		map = BC(TMX,"maps/Map1.tmx",4);
		server =  Address(GEK->server,7331);
		Player mc;
		socket.write(static_cast<Private*>(&mc),sizeof(Private),&server);
		while(socket.read(static_cast<Private*>(&mc),sizeof(Private))!=sizeof(Private)) puts("Esperando al puto servidor");;
		puts("Mensaje Recibido");
		id = mc.id;
		players[id] = mc;
		on[eK_KEYDOWN] = [&](const eK_Event & e){
			switch(e.key.keysym.sym){
				case '\033':
					std::exit(0);
					break;
				default:break;
			};
		};
	}
	Scene* operator()(){
		Player tmp;
		while(socket.read(static_cast<Status*>(&tmp),sizeof(Private))!=sizeof(Private));
		static_cast<Status&>(players[tmp.id]) = tmp;
		while(socket.read(static_cast<Status*>(&tmp),sizeof(Private))==sizeof(Private))
			static_cast<Status&>(players[tmp.id]) = tmp;
		map->camera(0, players[id].position+Vector2(0.5), GEK->screen/map->tile);
		map->camera(1, players[id].position+Vector2(0.5), GEK->screen/map->tile);
		for(auto& kv:players){
			kv.second.draw((kv.second.team=='G')?green:red,map);
			UI(*hp_fill,UI::root(),map->tracecast(kv.second.position+Vector2(0.5,-0.5)),{0.5,0.5},{static_cast<double>(kv.second.hp)/(1000),0.02*aspectratio}).draw();
		}
		switch(GEK->mouse.status){
			case (Mouse::L):
				players[id].target = map->raycast(GEK->mouse.position);
				break;
			case (Mouse::R):
				if(GEK->mouse.updated & Mouse::R)
					++(players[id].shoot);
			default:break;
		}
		socket.write(static_cast<Private*>(&players[id]),sizeof(Private),&server);
		tmp = players[id];
		players.clear();
		players[id] = tmp;
		return this;
	};
};
