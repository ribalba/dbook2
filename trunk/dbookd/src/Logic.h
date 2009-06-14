#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <yaml.h>
extern "C"{
#include "libdbook.h"
}
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
    void xDataReceived(XSocket* xSocket, string data);
    void xDisconnected();
    void xConnected();
  private:
    XSocket* listenSocket;
    vector<XSocket*> xSockets;
};
