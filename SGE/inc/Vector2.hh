#include <smmintrin.h>
union Vector2 {
	__m128d mm;
	struct{double x, y;};
	Vector2(__m128d m):mm(m){};
	Vector2(double xy):mm(_mm_set1_pd(xy)){};
	Vector2(double x, double y):mm(_mm_set_pd(y,x)){};
	Vector2 operator+(const Vector2 &o)const{return _mm_add_pd(mm, o.mm);}
	Vector2 operator-(const Vector2 &o)const{return _mm_sub_pd(mm, o.mm);}
	Vector2 operator*(const Vector2 &o)const{return _mm_mul_pd(mm, o.mm);}
	Vector2 operator/(const Vector2 &o)const{return _mm_div_pd(mm, o.mm);}
	Vector2 unit()const{return _mm_div_pd(mm,_mm_sqrt_pd(_mm_dp_pd(mm, mm, 0xFF)));}
	Vector2 clamp(const Vector2 &a,const Vector2 &b)const{return _mm_max_pd(_mm_min_pd(b.mm,mm),a.mm);}
	double mag()const{return _mm_cvtsd_f64(_mm_sqrt_pd(_mm_dp_pd(mm, mm, 0xFF)));}
};
