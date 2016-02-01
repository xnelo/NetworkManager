#include "Common/Sockets/ListeningSocket.hpp"
#include <cstring>  //needed for memset
#include <cerrno>   //needed to get error information about the socket
#include <unistd.h> //close function

ListeningSocket::ListeningSocket(SOCKET_ACTION_TYPE actionType, const char *ipAddress, int portNumber) :
    Socket(ipAddress, portNumber),
    _actionType(actionType)
{
    SOCKET_LOG(SOCKET_LOGGING_INFO, "Socket Initializing");
    //clear the socket make sure it is empty
    std::memset(&_socketInfo, 0, sizeof(_socketInfo));
    _socketInfo.sin_family = AF_INET;
    _socketInfo.sin_port = htons(_portNum);
    _socketInfo.sin_addr.s_addr = INADDR_ANY;

    //initialize the socket
    _socketNumber = socket(PF_INET, SOCK_STREAM, 0);
    if (!_socketNumber)
    {
        _error = "Create socket error: " + std::string(std::strerror(errno));
        _errorNumber = SOCKET_CREATION_ERROR;
        return;
    }

    SOCKET_LOG(SOCKET_LOGGING_DEBUG, "SocketNum: %d", _socketNumber);

    // set socket to immediately reuse port when the application closes
    int opt = 1;
    if (setsockopt(_socketNumber, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        _error = "setsockopt error: " + std::string(std::strerror(errno));
        close(_socketNumber);
        _socketNumber = 0;
        _errorNumber = SOCKET_CREATION_ERROR;
        return;
    }

    // call bind to associate the socket with our local address and
    // port
    if (bind(_socketNumber, (const struct sockaddr *)&_socketInfo, sizeof(_socketInfo)) < 0)
    {
        _error = "bind error: " + std::string(std::strerror(errno));
        close(_socketNumber);
        _socketNumber = 0;
        _errorNumber = SOCKET_CREATION_ERROR;
        return;
    }

    // convert the socket to listen for incoming connections
    if (listen(_socketNumber, SOMAXCONN) < 0)
    {
        _error = "listen error: " + std::string(std::strerror(errno));
        close(_socketNumber);
        _socketNumber = 0;
        _errorNumber = SOCKET_LISTEN_INIT_ERROR;
        return;
    }

    _error = "OK";
    _errorNumber = SOCKET_OK;
}

ListeningSocket::~ListeningSocket()
{
    SOCKET_LOG(SOCKET_LOGGING_INFO, "Socket Destroying");

    //close the socket
    if (_socketNumber > 0)
        close(_socketNumber);

    _socketNumber = 0;

}
