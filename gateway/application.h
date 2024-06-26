#ifndef APPLICATION_H
#define APPLICATION_H

#include "local_server.h"
#include "select_context.h"

typedef struct application {
  char* ipAddress;
  char* portNumber;

  char* gatewayServerPortNumber;
  LocalServer* localServer;

  SelectContext* selectContext;
} Application;

Application* application_new();

void application_delete(Application* application);

void application_launch(Application* application);

#endif  // APPLICATION_H
