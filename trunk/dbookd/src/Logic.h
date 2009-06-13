#include <string>
#include <iostream>
#include <vector>
#include <yaml.h>
#include "XSocket.h"

using namespace std;

class Logic : XSocketAdapter
{
  public:
    Logic();
    ~Logic();
    void run();
  protected:
    void xConnectionRequest(int sockfd);
    void xDataReceived(string data);
    void xDisconnected();
    void xConnected();
  private:
    XSocket* listenSocket;
    vector<XSocket*> xSockets;
};
