#include "server.h"

#include <stdlib.h> // malloc(), free(), exit()
#include <sys/socket.h> // socket()
#include <fcntl.h>  // fcntl()
#include <string.h> // memset()

#include "utility.h"

int _server_listen(char* portNumber) {
  const int listenSocketFD = socket(PF_INET, SOCK_STREAM, 0);
  utility_exitIfMinusOne(listenSocketFD);

  utility_setFDNonBlock(listenSocketFD);

  struct sockaddr_in serverSocketAddress;
  memset(&serverSocketAddress, 0, sizeof(serverSocketAddress));
  serverSocketAddress.sin_family = AF_INET;
  serverSocketAddress.sin_port = htons(portNumber);
  serverSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

  const int bindReturn = bind(listenSocketFD,
      (struct sockaddr*)&serverSocketAddress,
      sizeof(serverSocketAddress));
  utility_exitIfMinusOne(bindReturn);

  listen(listenSocketFD, 5);

  return listenSocketFD
}

Server* server_new(char* listenPortNumber) {
  Server* server = malloc(sizeof(server));
  server.listenSocketFD = listen();

  return server;
}

void server_delete(Server* server) {
  free(server);
}

int server_accept(Server* server) {
  struct sockaddr clientSocketAddress;
  socklen_t clientSocketAddressSize = sizeof(clientSocketAddress);
  const int clientSocketFD = accept(server->listenSocketFD,
      &clientSocketAddress,
      &clientSocketAddressSize);
  utility_exitIfMinusOne(clientSocketFD);

  return clientSocketFD;
}
