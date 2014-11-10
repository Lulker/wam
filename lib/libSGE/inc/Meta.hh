#ifdef __WIN32
	#define IF_WIN(w,l) w
#else
	#define IF_WIN(w,l) l
#endif

#ifdef NDEBUG
	#define debug_file(file)
	#define debug_var(var)
	#define debug_point(level)
	#define debug_assert(f,...) f
#else
	#include <cxxabi.h>
	#include <iostream>
	#define debug_file(file) (std::freopen(file,"w",stdout))
	#define debug_var(var) (std::cout << __FILE__ << ":" << __LINE__ << "\t" << __func__ << "\t\t" #var "( "<< abi::__cxa_demangle(typeid(var).name(), 0, 0, 0) << " ) = "<< var << "\n")
	#define debug_point(extra) (std::cout << __FILE__ << ":" << __LINE__ << "\t" << __func__ << extra "\n")
	#define debug_assert(f,...) f
	#//#define debug_assert(f,...) pimpl_assert(f __VA_ARGS__,[](){std::cout << __FILE__ << ":" << __LINE__ << "\t" << __func__ << "\n";})
#endif

template <class T, class T2> T pimpl_assert(T foo,T2 snafu){
	if((foo)) return foo;
	snafu(); exit(0);
}

template<class T> constexpr T *RRVALUE_PTR(T* x){return x;}
template<class T> constexpr T *RRVALUE_PTR(T x){return 0;}
template<class T> constexpr T &AUTO_DEFER(T* x){return *x;}	
template<class T> constexpr T &AUTO_DEFER(T x){return x;}

template<class T,class E> struct similar_to : std::integral_constant<bool,std::is_convertible<typename std::remove_pointer<typename std::decay<T>::type>::type,E>::value> {};
#define cttc(T,E) class = typename std::enable_if<similar_to<T,E>::value>
#define __ctstr(T) #T
#define ctstr(T) __ctstr(T)

class BCO {public: virtual ~BCO(){}};

class BackCollector : public BCO {
	const size_t chunk_size;
	size_t chunk_index;
	BCO** current_chunk;
	public:
		BackCollector(size_t chunk_size = 1024):chunk_size(chunk_size),chunk_index(chunk_size),current_chunk(new BCO*[chunk_size]){}
		template<class T, cttc(T,BCO), class... Args> T *BC(Args&&... args){
			T* object = new T(args...);
			debug_var(object);
			if(!(--chunk_index)){
				BCO** old_chunk = current_chunk;
				(current_chunk = new BCO*[chunk_size])[(chunk_index = chunk_index-2)+1] = reinterpret_cast<BCO*>(old_chunk);
			}
			current_chunk[chunk_index] = object;
			return object;
		}
		virtual ~BackCollector(){
			//collectables.clear();
		}
};
