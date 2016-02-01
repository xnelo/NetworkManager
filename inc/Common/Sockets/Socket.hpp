#ifndef ___NM_SOCKET_HPP__2015___
#define ___NM_SOCKET_HPP__2015___

#include <string>
#include <arpa/inet.h>

#ifdef INCLUDE_LOGGING
    #include "Common/Logger/Logging.hpp"
    #include <cstdarg>

    #define SOCKET_LOGGING_INFO LOGGING::INFO
    #define SOCKET_LOGGING_DEBUG LOGGING::DEBUG

    #define SOCKET_LOG(level, msg, ...) LOGGING::Logger::GetInstance()->Log(level, msg, ##__VA_ARGS__);
#else
    #define SOCKET_LOGGING_INFO 5
    #define SOCKET_LOGGING_DEBUG 6
    #define SOCKET_LOG(level, msg, ...) //do nothing
#endif

#define SOCKET_OK 0
#define SOCKET_CREATION_ERROR -1
#define SOCKET_LISTEN_INIT_ERROR -2

class Socket
{
protected:
    std::string _error; ///< A string with detailed information about the error.
    int _errorNumber; ///< An integer representing this classes error. 0 == OK.
    std::string _ipAddress;  ///< Ip address this socket is bound to.
    int _portNum; ///< Port number the socket is bound to.
    sockaddr_in _socketInfo; ///< Information about the socket to create.
    int _socketNumber; ///< The file descriptor number of the socket.
public:
    Socket(const char *ipAddress, int portNumber);
    virtual ~Socket();
    /**
     * Get the error number of this class. 0 == OK.
     * @return An integer of the error number.
     */
    int GetError();

    /**
     * Get additional information about the error.
     * @return A string with additional information about the error.
     */
    std::string & GetErrorString();

    /**
     * Get the file descriptor number for the socket.
     * @return An integer of the file descriptor for this socket.
     */
    int GetSocketNumber();
};

//-----------------------------------------------------------------------------
//
// Inline Function Implementation
//
//-----------------------------------------------------------------------------

inline Socket::Socket(const char * ipAddress, int portNumber) :
    _error("OK"),
    _errorNumber(SOCKET_OK),
    _ipAddress(ipAddress),
    _portNum(portNumber),
    _socketInfo(),
    _socketNumber(0)
{
    SOCKET_LOG(SOCKET_LOGGING_INFO, "Socket class initializing");
}

inline Socket::~Socket()
{
    SOCKET_LOG(SOCKET_LOGGING_INFO, "Socket class Destructing");
}

inline int Socket::GetError()
{
    return _errorNumber;
}

inline std::string & Socket::GetErrorString()
{
    return _error;
}

inline int Socket::GetSocketNumber()
{
    return _socketNumber;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// End Inline Function Implementation.
//-----------------------------------------------------------------------------

#endif // ___NM_SOCKET_HPP__2015___
