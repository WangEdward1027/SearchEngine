#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <string>
#include <arpa/inet.h> //struct sockaddr_in
using std::string;

class InetAddress
{
public:
    InetAddress(const string & ip, unsigned short port);
    InetAddress(const struct sockaddr_in &addr);
    ~InetAddress();
    string ip() const;
    unsigned short port() const;
    const struct sockaddr_in* getInetAddressPtr() const; 

private:
    struct sockaddr_in _addr;
};

#endif
