#include <scene/sGame.hh>
#include <scene/sMenu.hh>
#include <scene/sStart.hh>

#include <thread>
void server(const int);
#ifdef _WIN32
    #include <direct.h>
    #define chdir _chdir
#endif
int main(int argc, char const *argv[]){
    std::string name(argv[0]);
    const char *title = &name[0] + 1 + name.find_last_of(IF_WIN("\\","/"));
    *(&name[0] + name.find_last_of('.')) = 0;
    chdir(&name[0]);
    GEK::server = "127.0.0.1";
    if(argc>1){
        if(argv[1][0]=='h')
            std::thread(server,7331).detach();
        else
            GEK::server = argv[1];
    }
    return GEK::main(title,new sStart);
}
