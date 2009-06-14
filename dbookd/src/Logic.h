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

    void dbookd_check_isbn(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_isbn_10_to_13(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_isbn_13_to_10(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_sanitize(XSocket* xSocket, char *input);
    void dbookd_get_isbn_details(XSocket* xSocket, DBOOK_ISBN *inputISBN);

    //int dbook_is_isbn_13(DBOOK_ISBN *isbnToCheck);
    //int dbook_is_isbn_10(DBOOK_ISBN *isbnToCheck);
    //int dbook_genChkSum10(DBOOK_ISBN *isbnToTest);
    //int dbook_genChkSum13(DBOOK_ISBN *isbnToTest);
};
