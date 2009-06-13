#include "Logic.h"

Logic::Logic(){}
Logic::~Logic(){}

void Logic::run()
{
  string input;

  cout << "dbookd                      " << endl;
  cout << "------                      " << endl;
  cout << "type 'help' for instructions" << endl;
  cout << "                            " << endl;

  listenSocket = new XSocket(this, 1987);
  listenSocket->xListen();

  while(true)
  {
    cout << "> ";
    cin >> input;
  }

  return;
}

void Logic::xConnectionRequest(int sockfd)
{
  //cout << "\b\b" << "Connection Request" << endl;
  //cout << "> ";
  //flush(cout);
  xSockets.push_back(listenSocket->xAccept(sockfd));
}

void Logic::xDataReceived(string data)
{
  YAML::Emitter yaml;

  //cout << "\b\b" << "Data Received: " << data << endl;
  //cout << "> ";
  //flush(cout);

  yaml << YAML::BeginSeq;
  yaml << "eggs";
  yaml << "bread";
  yaml << "milk";
  yaml << YAML::EndSeq;
  cout << yaml.c_str() << endl;
}

void Logic::xConnected()
{
  cout << "\b\b" << "Client Connected: " << xSockets.size() - 1 << endl;
  cout << "> ";
  flush(cout);
}

void Logic::xDisconnected()
{
  for(int index = 0; index < xSockets.size(); index++)
  {
    if(xSockets[index]->connected == false)
    {
      delete xSockets[index];
      xSockets.erase(xSockets.begin() + index);
      cout << "\b\b" << "Client Disconnected: " << index << endl;
      cout << "> ";
      flush(cout);
    }
  }
}
