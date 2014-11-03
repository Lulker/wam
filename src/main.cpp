#include <scene/sStart.hpp>
#include <string>
#include <unistd.h>

int main(int argc, char const *argv[]){
	std::string name = argv[0];
	const char *program = &name[0] + 1 + name.find_last_of("/");
	*(&name[0] + name.find_last_of(".")) = 0;
	chdir(&name[0]);
	return (new eK(program,new sStart))->main();
}
