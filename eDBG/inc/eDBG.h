#pragma once
#include <unistd.h>
auto assert( auto f ){ if(f) return f; exit(0);};
#ifdef eDBG_ON
  #include <iostream>
  #define eDBG(foo) std::cout << #foo << ":" << __LINE__ << " = " << foo << std::endl;
  #define eDBG_FILE(foo) eDBG_INIT_HOOK_COUT(foo);
  void eDBG_INIT_HOOK_COUT(const char*);
#else
  #define eDBG(foo)
  #define eDBG_FILE(foo)
#endif
