#include <cstdio>
#include <iostream>

void eDBG_INIT_HOOK_COUT(const char* file){
  std::freopen(file,"w",stdout);
}
