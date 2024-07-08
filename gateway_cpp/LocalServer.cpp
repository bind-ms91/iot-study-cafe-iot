#include "LocalServer.hpp"

#include <string>
#include <unistd.h>  // close()
#include <sys/socket.h> // socket()
#include <fcntl.h>  // fcntl()
#include <cstring> // memset()
#include <arpa/inet.h>

#include "Utility.hpp"

int _listen(const std::string& portNumber) {
  const int listenSocketFD = socket(PF_INET, SOCK_STREAM, 0);
  exitIf(listenSocketFD == -1);

  FD::setNonBlock(listenSocketFD);

  struct sockaddr_in localServerSocketAddress;
  std::memset(&localServerSocketAddress, 0, sizeof(localServerSocketAddress));
  localServerSocketAddress.sin_family = AF_INET;
  localServerSocketAddress.sin_port = htons(atoi(portNumber.c_str()));
  localServerSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

  const int bindReturn = bind(listenSocketFD,
      (struct sockaddr*)&localServerSocketAddress,
      sizeof(localServerSocketAddress));
  exitIf(bindReturn == -1);

  fprintf(stderr, "[listen listenSocketFD : %d]\n", listenSocketFD);

  listen(listenSocketFD, 5);

  return listenSocketFD;
}

LocalServer::LocalServer(const std::string& listenPortNumber) {
  _listenSocketFD = _listen(listenPortNumber);
}

int LocalServer::listenSocketFD() const {
  return _listenSocketFD;
}

LocalServer::ClientSocketFDStreamMap& LocalServer::clientSocketFDStreamMap() {
  return _clientSocketFDStreamMap;
}

int _accept(int listenSocketFD) {
  struct sockaddr clientSocketAddress;
  socklen_t clientSocketAddressSize = sizeof(clientSocketAddress);
  const int clientSocketFD = accept(listenSocketFD,
      &clientSocketAddress,
      &clientSocketAddressSize);

  return clientSocketFD;
}

int LocalServer::accept() {
  int clientSocketFD = _accept(_listenSocketFD);
  if (clientSocketFD == -1) {
    return -1;
  }

  fprintf(stderr, "[accepted clientSocketFD : %d]\n", clientSocketFD);

  FD::setNonBlock(clientSocketFD);
  FD::setCanon(clientSocketFD);

  _clientSocketFDStreamMap.insert(std::make_pair(clientSocketFD, Stream(clientSocketFD)));

  return clientSocketFD;
}

void LocalServer::closeClientSocket(int fd) {
  close(fd);
  _clientSocketFDStreamMap.erase(fd);
}

const std::string* LocalServer::read(int fd) {
  Stream& stream = _clientSocketFDStreamMap[fd];

  ssize_t numberRead = stream.read();
  if (numberRead <= 0) {
    this->closeClientSocket(fd);
    return NULL;
  }

  return &stream.readBuffer();
}

void LocalServer::appendWriteBuffer(int fd, const std::string& string) {
  _clientSocketFDStreamMap[fd].appendWriteBuffer(string);
}

void LocalServer::write(int fd) {
  _clientSocketFDStreamMap[fd].write();
}
