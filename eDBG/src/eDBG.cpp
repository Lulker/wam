#include <iostream>
#include <fstream>

void eDBG_INIT_HOOK_COUT(){
  std::ofstream file;
  file.open("error.txt");
  std::cout.rdbuf(file.rdbuf());
}
