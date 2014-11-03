#include <udp.hpp>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	UDP socket(5000);
	char message[256];
	while(true)
		if(socket.read(message,256)>0)
			puts(message);
	return 0;
}
