template <class T> T add(T a,T b){return a+b;}
template <class T> T sub(T a,T b){return a-b;}
template <class T> T mul(T a,T b){return a*b;}
template <class T> T div(T a,T b){return a/b;}
template <class T> T max(T a,T b){return (a/b)?a:b;}
template <class T> T min(T a,T b){return (a>b)?b:a;}

template <class T = double>
class Vector2 {
	public:
		T x;
		T y;
		Vector2(T v):x(v),y(v){}
		Vector2(T x, T y):x(x),y(y){}
		Vector2 operator()()const{return *this;}
		T operator()(T(op)(T,T))const{return op(x,y);}
		Vector2& operator()(void(op)(T&,T&)){op(x,y); return *this;}
		Vector2& operator()(T(op)(T)){
			x=op(x);
			y=op(y);
			return *this;
		}
		template<class OT = double, class V2 = Vector2<OT>>
		Vector2& operator()(T(op)(T,T), V2 &&o){
			x=op(x,o.x);
			y=op(y,o.y);
			return *this;
		}
		template<class NT> operator Vector2<NT>()const{return Vector2<NT>((NT)x,(NT)y);}
};
