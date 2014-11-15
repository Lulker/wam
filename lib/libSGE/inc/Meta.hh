#ifdef __WIN32
	#define IF_WIN(w,l) w
#else
	#define IF_WIN(w,l) l
#endif

#ifdef NDEBUG
	#define debug_var(var)
#else
	#include <cxxabi.h>
	#include <iostream>
	#define debug_var(var) std::cout << __FILE__ << ":" << __LINE__ << "\t" << __func__ << "\t\t" #var "( "<< abi::__cxa_demangle(typeid(var).name(), 0, 0, 0) << " ) = "<< var << "\n"
#endif

#define assert(f) _pimpl_assert(f,__FILE__,__LINE__,__func__)
template <class T> T _pimpl_assert(T foo, const char *file, const int line, const char *function){
	if((foo)) return foo;
	printf("%s(%s):%d",file,function,line);
	exit(0);
}

template<class T> constexpr T &AUTO_DEFER(T* x){return *x;}
template<class T> constexpr T &AUTO_DEFER(T x){return x;}

#define cttc(T,E) class = typename std::enable_if<similar_to<T,E>::value>
template<class T,class E> struct similar_to : std::integral_constant<bool,std::is_convertible<typename std::remove_pointer<typename std::decay<T>::type>::type,E>::value> {};
class BCO {public: virtual ~BCO(){}};
class BackCollector : public BCO {
	std::vector<BCO*> lptd;
	public:
		BackCollector(size_t reserve = 1024){lptd.reserve(reserve);}
		//template<class T, cttc(T,BCO)> T *BC(){T* object = new T;lptd.push_back(object);return object;}
		template<class T, cttc(T,BCO), class... Args> T *BC(Args&&... args){
			T* object = new T(args...);
			debug_var(object);
			lptd.push_back(object);
			return object;
		}
		virtual ~BackCollector(){for(auto object:lptd){debug_var(object);delete object;}}
};
