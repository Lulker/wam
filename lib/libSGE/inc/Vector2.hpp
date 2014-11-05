template<class T> class Vector2 {
	public:
		T x;
		T y;
		Vector2(T v):x(v),y(v){};
		Vector2(T x, T y):x(x),y(y){};
		T angle(){return atan2(x,y)*180/M_PI;};
		Vector2 unit(){return Vector2(x/sqrt((x*x)+(y*y)),y/sqrt((x*x)+(y*y)));};
		Vector2& operator +=(const Vector2 o){x+=o.x;y+=o.y;return *this;};
		Vector2& operator -=(const Vector2 o){x-=o.x;y-=o.y;return *this;};
		Vector2& operator /=(const Vector2 o){x/=o.x;y/=o.y;return *this;};
		Vector2& operator *=(const Vector2 o){x*=o.x;y*=o.y;return *this;};
		template<class NT> operator Vector2<NT>()const{return Vector2<NT>((NT)x,(NT)y);}
};
