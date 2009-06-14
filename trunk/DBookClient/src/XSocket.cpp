#include "XSocket.h"

XSocket::XSocket(XSocketAdapter* parent, int port)
{
  this->parent = parent;
  this->port = port;
  connected = false;
}

XSocket::XSocket(XSocketAdapter* parent, string host, int port)
{
  this->parent = parent;
  this->host = host;
  this->port = port;
  connected = false;
}

XSocket::XSocket(XSocketAdapter* parent, string host, int port, int sockfd)
{
  pthread_t thread;

  this->parent = parent;
  this->host = host;
  this->port = port;
  this->sockfd = sockfd;
  connected = false;
  pthread_create(&thread, NULL, xReceiveThread, (void*)this);
}

XSocket::~XSocket(){}

bool XSocket::xConnect()
{
  int n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  pthread_t thread;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0)
  {
    return false;
  }

  server = gethostbyname(host.c_str());

  if(server == NULL)
  {
    return false;
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(port);

  if(connect(sockfd, (const sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
  {
    return false;
  }

  pthread_create(&thread, NULL, xReceiveThread, (void*)this);

  return true;
}

bool XSocket::xListen()
{
  pthread_t thread;
  struct sockaddr_in serv_addr;
  int n;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0) 
  {
    return false;
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
  {
    return false;
  }

  listen(sockfd, 5);
  pthread_create(&thread, NULL, xListenThread, (void*)this);

  return true;
}

XSocket* XSocket::xAccept(int sockfd)
{
  return new XSocket(parent, host, port, sockfd);
}

bool XSocket::xSend(string data)
{
  int n;

  if(connected == false)
  {
    return false;
  }

  data = data + '\n';

  n = write(sockfd, data.c_str(), data.length());

  if(n < 0)
  {
    return false;
  }

  return true;
}

void* xListenThread(void* xSocket)
{
  int newsockfd;
  struct sockaddr_in cli_addr;
  int clilen;

  clilen = sizeof(cli_addr);

  while(true)
  {
    newsockfd = accept(((XSocket*)xSocket)->sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    ((XSocket*)xSocket)->parent->xConnectionRequest(newsockfd);
  }
}

void* xReceiveThread(void* xSocket)
{
  char buffer[5120];
  stringstream ss;
  int n;

  ((XSocket*)xSocket)->connected = true;
  ((XSocket*)xSocket)->parent->xConnected();

  while(true)
  {
    bzero(buffer, 5120);
    ss.str("");
    n = read(((XSocket*)xSocket)->sockfd, buffer, 5119);

    if(n <= 0)
    {
      ((XSocket*)xSocket)->connected = false;
      ((XSocket*)xSocket)->parent->xDisconnected();
      return 0;
    }

    for(int index = 0; index < n; index++)
    {
      if(buffer[index] != '\n')
      {
        ss << buffer[index];
      }
      else
      {
        if(ss.str() != "")
        {
          ((XSocket*)xSocket)->parent->xDataReceived((XSocket*)xSocket, ss.str());
          ss.str("");
        }        
      }
    }

    //if(ss.str() != "")
    //{
    //  ((XSocket*)xSocket)->parent->xDataReceived(ss.str());
    //}
  }
}

XSocketAdapter::XSocketAdapter(){}
XSocketAdapter::~XSocketAdapter(){}
void XSocketAdapter::xConnectionRequest(int sockfd){}
void XSocketAdapter::xDataReceived(XSocket* xSocket, string data){}
void XSocketAdapter::xDisconnected(){}
void XSocketAdapter::xConnected(){}
