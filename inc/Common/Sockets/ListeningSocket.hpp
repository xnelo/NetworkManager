#ifndef ___NM_LISTENINGSOCKETS_HPP__2015___
#define ___NM_LISTENINGSOCKETS_HPP__2015___

#include <string>
#include "Socket.hpp"

enum SOCKET_CONNECTION_TYPE
{
    TCP_SOCKET,
    UDP_SOCKET
};

enum SOCKET_ACTION_TYPE
{
    LISTEN_SOCKET,
    SERVER_SOCKET = LISTEN_SOCKET,
    CLIENT_SOCKET
};

/**
 * The Socket Class.
 * Facilitates creation and using of sockets for network communication.
 */
class ListeningSocket : public Socket
{
private:
    SOCKET_ACTION_TYPE _actionType; ///< What kind of action is this socket.


public:
    /**
     * Constructor.
     * @param actionType What type of action does this socket perform. Listening or client communication.
     * @param ipAddress The IP address for this socket.
     * @param portNumber The port number this socket will listen on.
     */
    ListeningSocket(SOCKET_ACTION_TYPE actionType, const char * ipAddress, int portNumber);

    /**
      * Destructor.
      */
    ~ListeningSocket();

private:
    //-------------------------------------------------------------------------
    //
    // Hidden functions.
    //
    // These functions should never be used. Private functions that are used
    // will be outside this information block.
    //
    //-------------------------------------------------------------------------
    /*
     * Hide this function. A socket class should never be instantiated with the
     * default constructor.
     */
    ListeningSocket();

    /*
     * Hide this function. A socket class should NEVER be copied.
     */
    ListeningSocket(const ListeningSocket & other);

    /*
     * Hide this function A socket class should NEVER be copied or assigned to
     * another variable.
     */
    ListeningSocket & operator = (const ListeningSocket & other);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // End Hidden Functions
    //-------------------------------------------------------------------------
};

#endif //___NM_LISTENINGSOCKETS_HPP__2015___
