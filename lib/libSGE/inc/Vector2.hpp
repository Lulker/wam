template <class T = double> class Vector2 {
	public:
		T x;
		T y;
		Vector2(T v):x(v),y(v){};
		Vector2(T x, T y):x(x),y(y){};
		double angle(){return atan2(y,x)*180/M_PI;};
		double mag(){return x*y;}
		Vector2 unit(){return Vector2(x/sqrt((x*x)+(y*y)),y/sqrt((x*x)+(y*y)));};
		Vector2& operator +=(const Vector2 &o){x+=o.x;y+=o.y;return *this;};
		Vector2& operator -=(const Vector2 &o){x-=o.x;y-=o.y;return *this;};
		Vector2& operator *=(const Vector2 &o){x*=o.x;y*=o.y;return *this;};
		Vector2& operator /=(const Vector2 &o){x/=o.x;y/=o.y;return *this;};
		Vector2& operator +(Vector2 v){return v+=*this;};
		Vector2 operator -(Vector2 v){return Vector2(*this)-=v;};
		Vector2& operator *(Vector2 v){return v*=*this;};
		Vector2 operator /(Vector2 v){return Vector2(*this)/=v;};
		Vector2 operator +(const double &v){return *this+Vector2(v);};
		Vector2 operator -(const double &v){return *this-Vector2(v);};
		Vector2 operator *(const double &v){return *this*Vector2(v);};
		Vector2 operator /(const double &v){return *this/Vector2(v);};
		template<class NT> operator Vector2<NT>()const{return Vector2<NT>((NT)x,(NT)y);}
};
