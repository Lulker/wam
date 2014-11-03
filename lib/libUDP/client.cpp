#include <udp.hpp>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	UDP socket(1323);
	socket.to("127.0.0.1",5000);
	while(true)
		socket.send("Hello world",12);
	return 0;
}
