#include <cstdio>
#include <iostream>

void eDBG_INIT_HOOK_COUT(){
  std::freopen("error.txt","w",stdout);
}
