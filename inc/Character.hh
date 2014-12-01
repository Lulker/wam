Vector2 last = {12,1}
Vector2 spawn_point(){
  return last = (last+1).clamp({12,1},{17,3});
}

class Character : public Interactuable  {
int live;

public:
  Character():live(100){}
  ~Character(){}
  void damage(int hp){live-=hp;}
  void respawn(){move(spawn_point());}
  void shoot(Vector2 pos){
    double distancia = (pos-position).mag();

  }
  void immobilize(){}
};
