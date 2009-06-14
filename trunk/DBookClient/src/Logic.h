#include <string>
#include <sstream>
#include <iostream>
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
    void xDataReceived(XSocket* xSocket, string data);
    void xDisconnected();
    void xConnected();
  private:
    XSocket* xSocket;
};
