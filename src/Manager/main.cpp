#include "Common/Sockets/ConnectionSocket.hpp"
#include <iostream>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CONNECTION_ERROR -1

int main(int argc, char* argv[])
{
    std::cout << "Manager Starting" << std::endl;

    int portNum = 3000;
    std::string serverName = "127.0.0.1";
    ConnectionSocket * sock = new ConnectionSocket(serverName.c_str(), portNum);
    //int option;
    //bool running = true;

    //sockaddr_in server_conn;
    //int socketNum;
    //int socketOpt;

    //Set the connection information eg IP address
    //memset(&server_conn, 0, sizeof(server_conn));
    //server_conn.sin_family = AF_INET;
    //server_conn.sin_port = htons(portNum);
    //if (!inet_aton(serverName.c_str(), &server_conn.sin_addr))
    //{
    //    //printf("inet_addr() conversion error\n");
    //    std::cout << "inet_addr() conversion error" << std::endl;
    //    return CONNECTION_ERROR;
    //}

    ////get socket ID
    //socketNum = socket(PF_INET, SOCK_STREAM, 0);
    //if (socketNum < 0)
    //{
    //    std::cout << strerror(errno) << std::endl;
    //    return CONNECTION_ERROR;
    //}

    ////connect to the server
    //if (connect(socketNum, (const struct sockaddr *)&server_conn, sizeof(server_conn)) < 0)
    //{
    //    std::cout << strerror(errno) << std::endl;
    //    close(socketNum);
    //    return CONNECTION_ERROR;
    //}

    //send test message
    char * msg = "hello Server";
    send(sock->GetSocketNumber(), msg, 12, 0);
    //send(socketNum, msg, 12, 0);

    //close socket
    //close(socketNum);
    delete sock;

    std::cout << "Manager shutting down" << std::endl;
}
