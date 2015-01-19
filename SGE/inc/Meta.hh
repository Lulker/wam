#pragma once
#include <unordered_map>
#include <vector>
#ifdef _WIN32
	#define IF_WIN(w,l) w
#else
	#define IF_WIN(w,l) l
#endif

#ifdef NDEBUG
	#define debug_store_ptr(...) __VA_ARGS__
	#define debug(action,f,...) f(__VA_ARGS__)
#else
	#include <cstdio>
	#ifndef _MSC_VER
		#include <cxxabi.h>
		#define pimpl_demangle(v) abi::__cxa_demangle(v, 0, 0, 0)
	#else
		#define pimpl_demangle(v) v
	#endif
	extern std::unordered_map<void*,std::string> debug_db;
	template<class T> T *&debug_store_ptr(T *&&var){debug_db[var] = pimpl_demangle(typeid(var).name()); return var;}
	#define debug(des,fun,...) ([&](const char* f){printf("|%-11.11s:%-5d|%-30.30s|%s\n",[](std::string name){return &name[0] + 1 + name.find_last_of(IF_WIN("\\","/"));}(__FILE__),__LINE__,f,des);return fun(__VA_ARGS__);})(__FUNCTION__)
#endif

#define assert(v) debug("Asserting...",[](decltype(v) _){if(!(_))exit(0); return _;},v)
#define cttc(T,E) class = typename std::enable_if<similar_to<T,E>::value>
template<class T,class E> struct similar_to : std::integral_constant<bool,std::is_convertible<typename std::remove_pointer<typename std::decay<T>::type>::type,E>::value> {};

class BCO {public: virtual ~BCO(){}};
class BackCollector : public BCO {
	std::vector<BCO*> lptd;
	public:
		BackCollector(size_t reserve = 1024){lptd.reserve(reserve);}
		template<class T, cttc(T,BCO)> T *BC(){T* object = debug_store_ptr(new T);lptd.push_back(object);return object;}
		template<class T, cttc(T,BCO), class... Args> T *BC(Args&&... args){T* object = debug_store_ptr(new T(args...));lptd.push_back(object);return object;}
		virtual ~BackCollector(){for(auto& object:lptd) debug(&(debug_db[object])[0],delete,object);}
};
#define BC(T,...) debug(#T,BC<T>,__VA_ARGS__)
