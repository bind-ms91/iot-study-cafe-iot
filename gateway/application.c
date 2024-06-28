#include "application.h"

#include <stdlib.h>
#include <unistd.h>

#include "select_context.h"

//void application_readConfigurationFile(Application* application) {
//  Buffer* buffer = buffer_new();
//  scanf("%s\n", buffer->data);
//}

Application* application_new() {
  Application* application = malloc(sizeof(Application));

  SelectContext* const selectContext = selectContext_new();

  const char* localServerPortNumber = "9875";  // read from configuration.ini
  LocalServer* localServer = localServer_new_listenPortNumber(localServerPortNumber);

  selectContext_readFDSet_add(selectContext, localServer->listenSocketFD);

  application->localServer = localServer;
  application->selectContext = selectContext;

  return application;
}

void application_delete(Application* application) {
  selectContext_delete(application->selectContext);
  localServer_delete(application->localServer);
  free(application);
}

void _localServer_accept(Application* application) {
  const int gatewayClientFD = localServer_accept(application->localServer);
  if (gatewayClientFD == -1) {
    return;
  }

  selectContext_readFDSet_add(application->selectContext, gatewayClientFD);
}

void _remoteClient_close(Application* application) {
  selectContext_readFDSet_remove(application->selectContext, application->localServer->clientSocketFD);
  localServer_closeClientSocketFile(application->localServer);
}

void _loop(Application* application) {
  while (1) {
    selectContext_select(application->selectContext);

    if (selectContext_isSet(application->selectContext, application->localServer->listenSocketFD)) {
      if (application->localServer->clientSocketFD == -1) {
        _localServer_accept(application);
      }
    }

    if (selectContext_isSet(application->selectContext, application->localServer->clientSocketFD)) {
      char* readLineReturn = file_readLine(application->localServer->clientSocketFile);
      if (readLineReturn == NULL) {
        _remoteClient_close(application);
        continue;
      }

      Buffer* const readLineBuffer = application->localServer->clientSocketFile->readLineBuffer;
      write(1, readLineBuffer->data, readLineBuffer->count);
    }

    sleep(1);
  }
}

void application_launch(Application* application) {
  _loop(application);
}
