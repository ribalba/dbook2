#ifndef XSOCKET_H
#define XSOCKET_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <strings.h>
#include <pthread.h>

using namespace std;

class XSocket;
class XSocketAdapter;

class XSocketAdapter
{
  public:
    XSocketAdapter();
    ~XSocketAdapter();
    virtual void xConnectionRequest(int sockfd);
    virtual void xDataReceived(XSocket* xSocket, string data);
    virtual void xConnected();
    virtual void xDisconnected();
};

class XSocket
{
  public:
    XSocket(XSocketAdapter* parent, int port);
    XSocket(XSocketAdapter* parent, string host, int port);
    XSocket(XSocketAdapter* parent, string host, int port, int sockfd);
    ~XSocket();

    bool xListen();
    bool xConnect();
    XSocket* xAccept(int sockfd);
    bool xSend(string data);

    XSocketAdapter* parent;
    int sockfd;
    string host;
    int port;
    bool connected;
};

void* xListenThread(void* xSocket);
void* xReceiveThread(void* xSocket);

#endif
