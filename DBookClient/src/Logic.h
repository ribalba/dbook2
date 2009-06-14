#define BOOK_CACHE_SIZE 50

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <yaml.h>

extern "C"
{
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
    vector<dbook_book*> bookCache;

    void dbookd_check_isbn(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_isbn_10_to_13(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_isbn_13_to_10(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_sanitize(XSocket* xSocket, char *input);
    void dbookd_get_isbn_details(XSocket* xSocket, DBOOK_ISBN *inputISBN);
    void dbookd_is_isbn_13(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_is_isbn_10(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_genChkSum10(XSocket* xSocket, DBOOK_ISBN* inputISBN);
    void dbookd_genChkSum13(XSocket* xSocket, DBOOK_ISBN* inputISBN);
};
