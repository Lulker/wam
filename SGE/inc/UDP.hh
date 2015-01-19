#pragma once
#include <cstdlib>
#ifdef _WIN32
    #include <winsock2.h>
    #define IF_WIN(t,e) t
#else
    #define IF_WIN(t,e) e
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#define assert_sys(v) ([](decltype(v) _){if(intptr_t(_)==-1) exit(__LINE__); return _;}(v))
struct Address : sockaddr_in {
    Address(const unsigned short port = 0, const unsigned long ip = 0):sockaddr_in{}{
        sin_family=2;
        sin_port=htons(port);
        sin_addr.s_addr=htonl(ip);
    }
    Address(const char* ip, const unsigned short port = 0):sockaddr_in{}{
        sin_family=2;
        sin_port=htons(port);
        sin_addr.s_addr=inet_addr(ip);
    }
};

struct UDP {
    int sd;
    ~UDP(){IF_WIN(closesocket,close)(sd);}
    UDP(const unsigned short port = 0){
        #ifdef _WIN32
        WSADATA info;
        assert_sys(WSAStartup(514, &info));
        #endif
        long unsigned opt = 1;
        IF_WIN(ioctlsocket,ioctl)(sd = assert_sys(socket(2,2,0)), FIONBIO, &opt);
        sockaddr_in address = Address(port);
        assert_sys(bind(sd, reinterpret_cast<const sockaddr*>(&address), sizeof(sockaddr_in)));
    };
    void write(const void* buffer, const int len, const sockaddr_in* to)const{sendto(sd, (const char*)buffer, len, 0, (const sockaddr*)(to), sizeof(sockaddr_in));}
    const int read(void* buffer, const int len, sockaddr_in* from){IF_WIN(int,socklen_t) t = sizeof(sockaddr_in);return recvfrom(sd,(char*)buffer,len,0,reinterpret_cast<sockaddr*>(from),&t);}
    const int read(void* buffer, const int len)const{return recvfrom(sd,(char*)buffer,len,0,0,0);}
};
