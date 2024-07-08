#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "LocalServer.hpp"
#include "Select.hpp"

class Application {

public :
  Application();

  void launch();

private :
//  char* _ipAddress;
//  char* _portNumber;

//  char* _localServerPortNumber;
  LocalServer _localServer;

  Select _select;

  void _accept();

  void _loop();

};

#endif  // APPLICATION_HPP
