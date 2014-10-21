#pragma once
#ifdef eDBG_ON
  #include <iostream>
  #define eDBG(foo) std::cout << #foo << ":" << __LINE__ << " = " << foo << std::endl;
  #define eDBG_INIT eDBG_INIT_HOOK_COUT();
  void eDBG_INIT_HOOK_COUT();
#else
  #define eDBG(foo)
  #define eDBG_INIT
#endif
