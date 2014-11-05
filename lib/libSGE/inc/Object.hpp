class Object {
	Sprite *sprite;
	Vector2<double> target;
	Vector2<double> direction;
	double rotation;
	double speed;
	public:
		//Current position
		Vector2<double> position;
		/**
		* Creates an object
		* @param sprite sprite to create object from
		* @param position the object position in map
		* @param speed optional parameter to set object move speed in tiles per second
		* @param rotation optional parameter that sets initial rotation
		**/
		Object(Sprite &&sprite, Vector2<double> position, double speed = 0, double rotation = 0 ):sprite(&sprite),target(position),direction(0,0),rotation(rotation),speed(speed),position(position){};
		Object(Sprite *sprite, Vector2<double> position, double speed = 0, double rotation = 0 ):sprite(sprite),target(position),direction(0,0),rotation(rotation),speed(speed),position(position){};
		///Starts moving object to target map position
		void move(Vector2<double> target){direction = target.unit();}
		///Draws object in a map, using that map last camera render
		void draw(TMX *map){sprite->draw(Vector2<int>(map->tracecast(position)),rotation);}
		///Aims in the direction the object is going to move
		void aim(){rotation = direction.angle();}
		/**
		* Updates object position
		* @param deltatime time since last update
		**/
		void update(const double deltatime){position += (Vector2<double>(speed*deltatime) *= direction );}
};
