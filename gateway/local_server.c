#include "local_server.h"

#include <stdlib.h> // malloc(), free(), exit()
#include <sys/socket.h> // socket()
#include <fcntl.h>  // fcntl()
#include <string.h> // memset()
#include <arpa/inet.h>

#include "utility.h"

int _listen(const char* portNumber) {
  const int listenSocketFD = socket(PF_INET, SOCK_STREAM, 0);
  utility_exitIfMinusOne(listenSocketFD);

  fprintf(stderr, "listen listenSocketFD : %d\n", listenSocketFD);

  utility_fd_setNonBlock(listenSocketFD);

  struct sockaddr_in localServerSocketAddress;
  memset(&localServerSocketAddress, 0, sizeof(localServerSocketAddress));
  localServerSocketAddress.sin_family = AF_INET;
  localServerSocketAddress.sin_port = htons(atoi(portNumber));
  localServerSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

  const int bindReturn = bind(listenSocketFD,
      (struct sockaddr*)&localServerSocketAddress,
      sizeof(localServerSocketAddress));
  utility_exitIfMinusOne(bindReturn);

  listen(listenSocketFD, 5);

  return listenSocketFD;
}

LocalServer* localServer_new_listenPortNumber(const char* listenPortNumber) {
  LocalServer* localServer = malloc(sizeof(localServer));

  localServer->listenSocketFD = _listen(listenPortNumber);
  localServer->clientSocketFD = -1;

  return localServer;
}

void localServer_delete(LocalServer* localServer) {
  free(localServer);
}

int _accept(LocalServer* localServer) {
  struct sockaddr clientSocketAddress;
  socklen_t clientSocketAddressSize = sizeof(clientSocketAddress);
  const int clientSocketFD = accept(localServer->listenSocketFD,
      &clientSocketAddress,
      &clientSocketAddressSize);
  utility_exitIfMinusOne(clientSocketFD);

  return clientSocketFD;
}

int localServer_accept(LocalServer* localServer) {
  if (localServer->clientSocketFD != -1) {
    return -1;
  }

  int clientSocketFD = _accept(localServer);
  fprintf(stderr, "accepted clientSocketFD : %d\n", clientSocketFD);

  utility_fd_setNonBlock(clientSocketFD);
  utility_fd_setCanon(clientSocketFD);

  localServer->clientSocketFD = clientSocketFD;
  localServer->clientSocketFile = file_new_fd(clientSocketFD, "a+");

  return clientSocketFD;
}

void localServer_closeClientSocketFile(LocalServer* localServer) {
  file_delete(localServer->clientSocketFile);
  localServer->clientSocketFile = NULL;
  localServer->clientSocketFD = -1;
}
