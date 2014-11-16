#include <unordered_map>
#include <vector>
#ifdef __WIN32
	#define IF_WIN(w,l) w
#else
	#define IF_WIN(w,l) l
#endif

#ifdef NDEBUG
	#define debug_store_ptr(...) __VA_ARGS__
	#define debug(action,f,...) f(__VA_ARGS__)
#else
	#include <cxxabi.h>
	#include <cstdio>
	extern std::unordered_map<void*,std::string> debug_db;
	template<class T> T *&debug_store_ptr(T *&&var){debug_db[var] = IF_WIN(typeid(var).name(),abi::__cxa_demangle(typeid(var).name(), 0, 0, 0));return var;}
	#define debug(des,fun,...) ([&](const char* f){printf("|%-20s:%-5d|%-20s|%-20s|%.*s\n",__BASE_FILE__,__LINE__,f,des,224-71,#__VA_ARGS__);return fun(__VA_ARGS__);})(__func__)
#endif

#define assert(v) debug("Asserting...",([&](auto _){if((_)) return _; exit(0);}),v)

#define chain(...) auto __VA_ARGS__; return this;}

#define cttc(T,E) class = typename std::enable_if<similar_to<T,E>::value>
template<class T,class E> struct similar_to : std::integral_constant<bool,std::is_convertible<typename std::remove_pointer<typename std::decay<T>::type>::type,E>::value> {};

class BCO {public: virtual ~BCO(){}};
class BackCollector : public BCO {
	std::vector<BCO*> lptd;
	public:
		BackCollector(size_t reserve = 1024){lptd.reserve(reserve);}
		template<class T, cttc(T,BCO)> T *BC(){T* object = debug_store_ptr(new T);lptd.push_back(object);return object;}
		template<class T, cttc(T,BCO), class... Args> T *BC(Args&&... args){T* object = debug_store_ptr(new T(args...));lptd.push_back(object);return object;}
		virtual ~BackCollector(){for(auto& object:lptd) debug(&("delete "+debug_db[object])[0],[&](){delete object;});}
};
#define BC(T,...) debug(#T,BC<T>,__VA_ARGS__)
