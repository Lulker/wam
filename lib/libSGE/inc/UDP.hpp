class UDP
{
	private:
		struct sockaddr_in address = {};
		int ld;
	public:
		~UDP();
		UDP(unsigned short port = 0);
		void to(unsigned long ip, unsigned short port){
			address.sin_addr.s_addr = ip;
			address.sin_port = port;
		}
		void to(const char* ip, unsigned short port){to(inet_addr(ip),htons(port));}
		void write(const char* buffer, int len) {sendto(ld, buffer, len, 0, reinterpret_cast<const sockaddr*>(&address), sizeof(sockaddr_in));}
		int readfrom(char* buffer, int len) {return recvfrom(ld,buffer,len,0,reinterpret_cast<sockaddr*>(&address),0);}
		int read(char* buffer, int len) {return recvfrom(ld,buffer,len,0,0,0);}
};
