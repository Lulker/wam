#include <SGE.hh>
using namespace SGE;
#include <scene/sGame.hh>
#include <scene/sStart.hh>

int main(int argc, char const *argv[]){
  std::string name(argv[0]);
  const char *title = &name[0] + 1 + name.find_last_of(IF_WIN("\\","/"));
  *(&name[0] + name.find_last_of('.')) = 0;
  chdir(&name[0]);
  return SGE::GEK::main(title,new sStart);
}
