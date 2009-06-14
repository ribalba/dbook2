#include "Logic.h"

Logic::Logic(){}
Logic::~Logic(){}

void Logic::run()
{
  string host;
  int port;
  string input;

  cout << "DBook Client    " << endl;
  cout << "------------    " << endl;
  cout << "'ctrl-c' to quit" << endl;
  cout << "                " << endl;

  cout << "host: ";
  cin >> host;
  cout << "port: ";
  cin >> port;

  xSocket = new XSocket(this, host, port);  

  if(xSocket->xConnect() == false)
  {
    cout << "Error: Could not connect" << endl;
    return;
  }

  while(true)
  {
    cout << "> ";
    cin >> input;

    YAML::Emitter yaml;
    yaml << YAML::BeginMap;
    yaml << YAML::Key << "function";
    yaml << YAML::Value << "dbook_get_isbn_details";
    yaml << YAML::Key << "isbn";
    yaml << YAML::Value << "0330267388";
    yaml << YAML::EndMap;

    xSocket->xSend(yaml.c_str());
  }

  return;
}

void Logic::xDataReceived(XSocket* xSocket, string data)
{
  cout << "Data Received: " << data << endl;
}

void Logic::xConnected()
{
  cout << "Connected" << endl;
}

void Logic::xDisconnected()
{
  cout << "Disconnected" << endl;
}
