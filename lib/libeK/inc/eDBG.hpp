#pragma once
#include <stdlib.h>
auto assert( auto f ){ if(f) return f; exit(0);};
#ifdef eDBG_ON
  #include <cstdio>
  #include <iostream>
  #define eDBG(foo) std::cout << #foo << ":" << __LINE__ << " = " << foo << std::endl;
  #define eDBG_FILE(foo) std::freopen(foo,"w",stdout);
#else
  #define eDBG(foo)
  #define eDBG_FILE(foo)
#endif
