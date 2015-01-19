#include <Player.hh>
#include <CMWC.hh>
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
Vector2 spawn_position(const char team){return (team=='R')?Vector2(irand(12,17),irand(37,39)):Vector2(irand(12,17),irand(1,3));}
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
    for(;const double deltatime = 3*std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now()-nao).count();){
        nao = std::chrono::high_resolution_clock::now();
        mutex.lock();
        for(auto& update:players){
            update.update(Vector2(deltatime));
            if(update.shoot != update.shooted){
                for(auto& player:players)
                    if(&player!=&update && hit(
                        update.position,
                        update.position+update.direction*100,
                        player.position+Vector2(0.5)+Vector2(-update.direction.y,update.direction.x),
                        player.position+Vector2(0.5)-Vector2(-update.direction.y,update.direction.x)
                    ))
                        if((player.hp -= irand(15,35))<0)
                            player.respawn(spawn_position(player.team),spawn_rotation(player.team));
                update.shoot = update.shooted;
            }
            for(auto& player:players)
                sock->write(static_cast<Status*>(&player),sizeof(Private),&update.address);
        }
        mutex.unlock();
    }
}

const bool anticheat( const Private& player ){
    return (players[player.id].secret == player.secret);
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
