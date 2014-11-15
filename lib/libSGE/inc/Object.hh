class Object : public BCO {
	Sprite *sprite;
	Vector2<> target;
	Vector2<> direction;
	double rotation;
	double speed;
	public:
		/**
		* Creates an object
		* @param sprite sprite to create object from
		* @param position the object position in map
		* @param speed optional parameter to set object move speed in tiles per second
		* @param rotation optional parameter that sets initial rotation
		**/
		Object(Sprite *sprite, Vector2<> position, double speed = 0, double rotation = 0 ):sprite(sprite),target(position),direction(0,0),rotation(rotation),speed(speed),position(position){}
		//Current position
		Vector2<> position;
		///Starts moving object to target map position
		Object &move(Vector2<> new_target){direction = (direction = (target=new_target)()(sub,position))(div,{sqrt(direction()(mul,direction)(add))});return *this;}
		///Draws object in screen, using a map last camera render
		template<class T,cttc(T,TMX)> Object &draw(T &&map){sprite->draw(map->tracecast(position),rotation);return *this;}
		///Aims in the direction the object is going to move
		Object &aim(){rotation = direction()(std::swap)(atan2)*180/M_PI;return *this;}
		/**
		* Updates object position
		* @param deltatime time since last update
		**/
		Object &update(const double deltatime){
			if(target()(sub,position)(mul)>0.05)
				position(add,direction()(mul,{speed*deltatime}));
			return *this;
		}
};
