#ifndef ___NM_CONNECTIONSOCKET_HPP__2015___
#define ___NM_CONNECTIONSOCKET_HPP__2015___

#include <string>
#include "Socket.hpp"

class ConnectionSocket : public Socket
{
public:
    ConnectionSocket(const char *ipAddress, int portNumber);
    ~ConnectionSocket();
};

#endif // ___NM_CONNECTIONSOCKET_HPP__2015___
