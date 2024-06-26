#ifndef LOCAL_SERVER_H
#define LOCAL_SERVER_H

#include "file.h"

typedef struct localServer {
  int listenSocketFD;

  int clientSocketFD;
  File* clientSocketFile;
} LocalServer;

//LocalServer* localServer_new();
LocalServer* localServer_new_listenPortNumber(const char* listenPortNumber);

void localServer_delete(LocalServer* localServer);

int localServer_accept(LocalServer* localServer);

#endif  // LOCAL_SERVER_H
