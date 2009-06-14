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

void Logic::xDataReceived(XSocket* xSocket, string data)
{
  stringstream ss;
  YAML::Node node;
  string function;
  string isbn;
  int result;

  cout << "\b\b" << "Data Received: " << data << endl;
  cout << "> ";
  flush(cout);

  ss << data;
  YAML::Parser parser(ss);
  parser.GetNextDocument(node);
  node["function"] >> function;

  if(function == "dbook_check_isbn")
  {
    node["isbn"] >> isbn;
    dbookd_check_isbn(xSocket, (char*)isbn.c_str());
  }

  if(function == "dbookd_isbn_10_to_13")
  {
    node["isbn"] >> isbn;
    dbookd_check_isbn(xSocket, (char*)isbn.c_str());
  }

  //YAML::Emitter yaml;
  //yaml << YAML::BeginMap;
  //yaml << YAML::Key << "function";
  //yaml << YAML::Value << "check_isbn";
  //yaml << YAML::Key << "isbn";
  //yaml << YAML::Value << "0123456789123";
  //yaml << YAML::EndMap;

  //yaml << YAML::BeginSeq;
  //yaml << "eggs";
  //yaml << "bread";
  //yaml << "milk";
  //yaml << YAML::EndSeq;
  //cout << yaml.c_str() << endl;
}

void Logic::dbookd_check_isbn(XSocket* xSocket, DBOOK_ISBN *inputISBN)
{
  YAML::Emitter yaml;
  int result;

  result = dbook_check_isbn(inputISBN);

  yaml << YAML::BeginMap;
  yaml << YAML::Key << "result";
  yaml << YAML::Value << result;
  yaml << YAML::EndMap;
  xSocket->xSend(yaml.c_str());
}

void Logic::dbookd_isbn_10_to_13(XSocket* xSocket, DBOOK_ISBN* inputISBN)
{
  YAML::Emitter yaml;
  int result;
  DBOOK_ISBN* outputISBN;

  result = dbook_isbn_10_to_13(inputISBN, outputISBN);

  yaml << YAML::BeginMap;
  yaml << YAML::Key << "isbn";
  yaml << YAML::Value << outputISBN;
  yaml << YAML::EndMap;
  xSocket->xSend(yaml.c_str());
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
