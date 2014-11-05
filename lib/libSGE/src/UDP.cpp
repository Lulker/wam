#include <SGE.hpp>
#ifdef _WIN32
	#define ioctl ioctlsocket
	#define close closesocket
#else
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
#endif

SGE::UDP::UDP(unsigned short port) {
	#ifdef _WIN32
	WSADATA info;
	assert(WSAStartup(514, &info));
	#endif
	assert((ld = socket(2,2,0)),==-1);
	long unsigned opt = 1;
	ioctl(ld, FIONBIO, &opt);
	address.sin_family = 2;
	address.sin_port = htons(port);
	assert(bind(ld, reinterpret_cast<const sockaddr*>(&address), sizeof(sockaddr_in)),==-1);
}

SGE::UDP::~UDP(){
	close(ld);
}
