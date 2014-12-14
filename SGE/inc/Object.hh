class Object : public BCO {
	Sprite *sprite;
	public:
		Vector2 target;
		Vector2 direction;
		double rotation;
		double speed;
		//Current position
		Vector2 position;
		/**
		* Creates an object
		* @param sprite sprite to create object from
		* @param position the object position in map
		* @param speed optional parameter to set object move speed in tiles per second
		* @param rotation optional parameter that sets initial rotation
		**/
		Object(Sprite *sprite, const Vector2 &position, double speed = 0, double rotation = 0 ):sprite(sprite),target(position),direction(0,0),rotation(rotation),speed(speed),position(position){}
		///Starts moving object to target map position
		void move(const Vector2 &new_target){direction = ((target = new_target-0.5)-position).unit();}
		///Draws object in screen, using a map last camera render
		template<class T,cttc(T,TMX*)> void draw(T &&map)const{sprite->draw(map->tracecast(position),rotation);}
		///Aims in the direction of a vector2
		void aim(const Vector2 &aimto){
			target = position;
			direction = ((aimto-0.5)-position).unit();
			aim();
		}
		///Aims in the direction the object is going to move
		void aim(){rotation = atan2(direction.y,direction.x)*180/M_PI;}
		///Updates object position based on time since last update
		void update(const double deltatime){if((target-position).mag()>0.25) position = position + direction*Vector2(speed*deltatime);}
};
