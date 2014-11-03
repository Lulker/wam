#include <udp.hpp>
#ifdef _WIN32
	#define ioctl ioctlsocket
	#define close closesocket
#else
	#include <sys/socket.h>
#endif

UDP::UDP(int port) {
	#ifdef _WIN32
	WSADATA info;
	if(WSAStartup(514, &info))throw;
	#endif
	if((ld = socket(2,2,0))==-1)throw;
	long unsigned opt = 1;
	ioctl(ld, 0x4004667e, &opt);
	address.sin_family = 2;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_size = sizeof(sockaddr_in);
	if(bind(ld, reinterpret_cast<const sockaddr*>(&address), addr_size)==-1)throw;
}

UDP::~UDP(){
	close(ld);
}
