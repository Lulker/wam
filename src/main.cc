#include <scene/sStart.hh>
#include <GEK.hh>
#include <string>
#ifdef _WIN32
    #include <direct.h>
    #define chdir _chdir
#else
    #include <unistd.h>
#endif

GameEngineKernel *GEK;

int main(int argc, char const *argv[]){
    std::string name(argv[0]);
    *(&name[0] + name.find_last_of('.')) = 0;
    chdir(&name[0]);
    GEK = new GameEngineKernel(&name[0] + 1 + name.find_last_of(IF_WIN("\\","/")),"127.0.0.1");
    if(argc>1) GEK->server = argv[1];
    return GEK->loop(new sStart);
}
