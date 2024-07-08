#ifndef LOCALSERVER_HPP
#define LOCALSERVER_HPP

#include <string>
#include <map>

#include "Stream.hpp"

class LocalServer {

public :
  typedef std::map<int, Stream> ClientSocketFDStreamMap;

  LocalServer(const std::string& listenPortNumber);

  int listenSocketFD() const;
  ClientSocketFDStreamMap& clientSocketFDStreamMap();

  int accept();
  void closeClientSocket(int fd);

  const std::string* read(int fd);
  void write(int fd, const std::string& string = "");

private :
  int _listenSocketFD;
  ClientSocketFDStreamMap _clientSocketFDStreamMap;

};

#endif  // LOCALSERVER_HPP
