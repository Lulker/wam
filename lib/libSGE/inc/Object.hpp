class Object {
	Sprite *sprite;
	Vector2<> target;
	Vector2<> direction;
	double rotation;
	double speed;
	bool rvalue;
	public:
		~Object(){if(rvalue) delete sprite;}
		//Current position
		Vector2<> position;
		/**
		* Creates an object
		* @param sprite sprite to create object from
		* @param position the object position in map
		* @param speed optional parameter to set object move speed in tiles per second
		* @param rotation optional parameter that sets initial rotation
		**/
		//LVALUE
		Object(Sprite *&sprite, Vector2<> position, double speed = 0, double rotation = 0 ):sprite(sprite),target(position),direction(0,0),rotation(rotation),speed(speed),rvalue(0),position(position){};
		//RVALUE
		Object(Sprite *&&sprite, Vector2<> position, double speed = 0, double rotation = 0 ):sprite(sprite),target(position),direction(0,0),rotation(rotation),speed(speed),rvalue(1),position(position){};
		///Starts moving object to target map position
		void move(Vector2<> target){
			this->target = target;
			direction = (target-position).unit();
		}
		///Draws object in screen, using a map last camera render
		void draw(TMX *map){sprite->draw(map->tracecast(position),rotation);}
		///Aims in the direction the object is going to move
		void aim(){rotation = direction.angle();}
		/**
		* Updates object position
		* @param deltatime time since last update
		**/
		void update(const double deltatime){
			if((target-position).mag()>0.25)
				position += (Vector2<>(speed*deltatime) *= direction);
		}
};
