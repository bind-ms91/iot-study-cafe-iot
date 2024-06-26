#include "application.h"

#include <stdlib.h>
#include <unistd.h>

//void application_readConfigurationFile(Application* application) {
//  Buffer* buffer = buffer_new();
//  scanf("%s\n", buffer->data);
//}

Application* application_new() {
  Application* application = malloc(sizeof(Application));

  const SelectContext selectContext = selectContext_new();

  const char* gatewayServerPortNumber = "9876";  // read from configuration.ini
  const Server* gatewayServer = server_new_listenPortNumber(gatewayServerPortNumber);

  int serverListenSocketFD = gatewayServer->listenSocketFD;
  selectContext_readFDSet_add(selectContext, serverListenSocketFD);

  application->selectContext = selectContext;
  application->gatewayServer = gatewayServer;

  return application;
}

void application_delete(Application* application) {
  server_delete(application->gatewayServer);
  selectContext_delete(application->selectContext);
  free(application);
}

void application_launch(Application* application) {
  application_loop(application);
}

void application_loop(Application* application) {
  while (1) {
    selectContext_select(application->selectContext);

    const SelectContext* selectContext = application->selectContext;
    const int gatewayServerListenSocketFD = application->gatewayServer->listenSocketFD;
    if (selectContext_isSet(selectContext, gatewayServerListenSocketFD)) {
      const Server* gatewayServer = application->gatewayServer;
      application->gatewayClientFD = server_accept(gatewayServer);
    }
    sleep(1);
  }
}
