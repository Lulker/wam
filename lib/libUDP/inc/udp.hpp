#pragma once
#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <netinet/in.h>
#endif

class UDP
{
	private:
		struct sockaddr_in address;
		int addr_size;
		int ld;
	public:
		~UDP();
		UDP(int port = 3257);
		inline void rawto(unsigned long ip, unsigned short port){
			address.sin_addr.s_addr = ip;
			address.sin_port = port;
		};
		inline void to(const char* ip, unsigned short port){
			rawto(inet_addr(ip),htons(port));
		};
		inline void send(const char* buffer, int len) {
			sendto(ld, buffer, len, 0, reinterpret_cast<const sockaddr*>(&address), addr_size);
		};
		inline void whois(unsigned long &addr, unsigned short &port) {
			port = address.sin_port;
			addr = address.sin_addr.s_addr;
		};
		inline int read(char* buffer, int len) {
			return recvfrom(ld, buffer, len, 0, reinterpret_cast<sockaddr*>(&address), &addr_size);
		};
};
