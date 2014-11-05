#ifdef __WIN32
	#define IF_WIN(w,l) w
#else
	#define IF_WIN(w,l) l
#endif

#ifdef eDBG_ON
	#include <cstdio>
	#include <iostream>
	#define eDBG(foo) std::cout << #foo << ":" << __LINE__ << " = " << foo << std::endl
	#define eDBG_FILE(foo) freopen(foo,"w",stdout)
	#define assert(v,...) ((v...)?v:throw std::string(__FILE__)+":"+std::string(__LINE__))
#else
	#define eDBG(foo)
	#define eDBG_FILE(foo)
	#define assert(v,...) v
#endif

