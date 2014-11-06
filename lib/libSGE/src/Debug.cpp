#include <SGE.hpp>
#include <cstdio>
void SGE::__debug(const char* file,const int line,const char* function,const char* alt){printf("%s:%d\t%s\t%s\n",file,line,function,alt);};