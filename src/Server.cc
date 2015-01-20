#include <functional>
#include <Player.hh>
#include <CMWC.hh>
#include <Map.hh>
#include <UDP.hh>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>

std::mutex mutex;
std::vector<Player> players;
std::chrono::system_clock::time_point nao;
const int vrand(){static CMWC irand(time(0));int tmp = 0;return (tmp = irand())?tmp:vrand();}

CMWC irand(time(0));
Vector2 spawn_position(const char team){return (team=='R')?Vector2(irand(12,17),irand(38,40)):Vector2(irand(12,17),irand(1,3));}
double spawn_rotation(const char team){return (team=='R')?Vector2(0,-1).angle():Vector2(0,1).angle();};
char assign_team(){
    int reds = 0, greens = 0;
    for(auto& player:players) ++((player.team=='R')?reds:greens);
    return (reds>greens)?'G':'R';
}

char hit(const Vector2 p0,const Vector2 p1,const Vector2 p2,const Vector2 p3){
    Vector2 s1 = p1 - p0;
    Vector2 s2 = p3 - p2;
    double s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y); //TODO:optimize for SSE
    double t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);
    return (s >= 0 && s <= 1 && t >= 0 && t <= 1);
}

void logic(UDP *sock){
    const Map map("maps/Map1.tmx");
    const std::function<bool(const Vector2,const Vector2)>& collision = [&map](const Vector2 p, const Vector2 d){
        return (map(p.x,p.y+copysign(0.5,d.y))==-1) && (map(p.x+copysign(0.5,d.x),p.y)==-1);
    };
    for(;;){
        const double deltatime = 3*std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now()-nao).count();
        nao = std::chrono::high_resolution_clock::now();
        mutex.lock();
        puts("1111111111111111");
        for(auto& update:players){
            update.update(Vector2(deltatime),collision);
            if(update.shoot != update.shooted){
                const Vector2 map_bound = map.raycast(update.position,update.direction);
                const Vector2 llimit = Vector2(0.5)+Vector2(-update.direction.y,update.direction.x);
                const Vector2 ulimit = Vector2(0.5)-Vector2(-update.direction.y,update.direction.x);
                for(auto& player:players)
                    if(&player!=&update && hit(update.position,map_bound,player.position+llimit,player.position+ulimit) && (player.hp -= irand(15,35))<0){
                        ++update.score;
                        player.respawn(spawn_position(player.team),spawn_rotation(player.team));
                    }
                update.shoot = update.shooted;
            }
            std::vector<Vector2> visibles;
            sock->write(static_cast<Status*>(&update),sizeof(Status),&update.address);
            map.fov(visibles,update.position.x+0.5,update.position.y+0.5,10);
            for(auto& player:players)
                for(auto& v:visibles)
                    if(int(player.position.x)==v.x && int(player.position.y)==v.y){
                        sock->write(static_cast<Status*>(&player),sizeof(Status),&update.address);
                        break;
                    }
        }
        mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

const bool anticheat( const Private& player ){
    return (players[player.id].secret == player.secret && players[player.id].ban<nao);
}

void handler(UDP *sock){
    int size;
    for(Player player;;) while((size = sock->read(static_cast<Private*>(&player),sizeof(Private),&player.address))==sizeof(Private))
        if(!player.secret){
            mutex.lock();
            char tmp = assign_team();
            players.push_back(Player(vrand(),players.size(),tmp,player.address,spawn_position(tmp),spawn_rotation(tmp)));
            sock->write(static_cast<Private*>(&players.back()),sizeof(Private),&players.back().address);
            mutex.unlock();
        } else if (player.id<players.size() && anticheat(player)){
            players[player.id].shoot = player.shoot;
            players[player.id].target = player.target;
        }
}

void server(const int port){
    UDP sock(port);
    std::thread(logic,&sock).detach();
    std::thread(handler,&sock).join();
}
