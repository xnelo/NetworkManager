#include "Common/Sockets/ConnectionSocket.hpp"
#include <cstring>  //needed for memset
#include <cerrno>   //needed to get error information about the socket
#include <unistd.h> //close function

ConnectionSocket::ConnectionSocket(const char *ipAddress, int portNumber):
    Socket(ipAddress, portNumber)
{

    //Set the connection information eg IP address
    memset(&_socketInfo, 0, sizeof(_socketInfo));
    _socketInfo.sin_family = AF_INET;
    _socketInfo.sin_port = htons(_portNum);
    if (!inet_aton(_ipAddress.c_str(), &_socketInfo.sin_addr))
    {
        //printf("inet_addr() conversion error\n");
        _error = "inet_addr() conversion error";
        _errorNumber = SOCKET_CREATION_ERROR;
        return;
    }

    //get socket ID
    _socketNumber = socket(PF_INET, SOCK_STREAM, 0);
    if (_socketNumber < 0)
    {
        _error = std::string(std::strerror(errno));
        _errorNumber = SOCKET_CREATION_ERROR;
        return;
    }

    //connect to the server
    if (connect(_socketNumber, (const struct sockaddr *)&_socketInfo, sizeof(_socketInfo)) < 0)
    {
        _error = std::string(std::strerror(errno));
        close(_socketNumber);
        _errorNumber = SOCKET_CREATION_ERROR;
        return;
    }
}

ConnectionSocket::~ConnectionSocket()
{
    //SOCKET_LOG(SOCKET_LOGGING_INFO, "Socket Destroying");

    //close the socket
    if (_socketNumber > 0)
        close(_socketNumber);

    _socketNumber = 0;
}
