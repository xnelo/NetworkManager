#include "Common/Logger/Logging.hpp"
#include "Common/Sockets/ListeningSocket.hpp"
//#include <cstring> //needed for memset
//#include <cerrno> //needed to get error information about sockets.
#include <arpa/inet.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
#include <unistd.h> //close function

#define CONNECTION_ERROR -1

int main(int argc, char * argv[])
{
    LOGGING::Logger * logger = LOGGING::Logger::GetInstance();
    logger->LogAndPrint(LOGGING::INFO, "Agent Starting");

    int portNum = 3000;

    ListeningSocket * sock = new ListeningSocket(LISTEN_SOCKET, "127.0.0.1", portNum);
    if (sock->GetError() != 0)
    {
        logger->LogAndPrint(LOGGING::CRITICAL, sock->GetErrorString());
        return CONNECTION_ERROR;
    }

    //accept incoming requests
    int c;
    int nread;
    sockaddr_in client;
    socklen_t clientlen = sizeof(client);
    char *buf = new char[1024];
    while ((c = accept(sock->GetSocketNumber(), (struct sockaddr *)&client, &clientlen)) > 0)
    {
        logger->Log(LOGGING::INFO, "Accepting connections #%d", c);

        recv(c, buf, 1024, 0);
        logger->LogAndPrint(LOGGING::INFO, buf);

        logger->Log(LOGGING::INFO, "Closing Connection #%d", c);
        close(c);
    }

    //clean up buffer
    delete buf;

    //close the socket
    //close(socketNum);
    delete sock;
    sock = NULL;

    logger->LogAndPrint(LOGGING::INFO, "Agent Closing");
}
