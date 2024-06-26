#include "application.h"

#include <stdlib.h>

void application_readConfigurationFile(Application* application) {
  Buffer* buffer = buffer_new();
  scanf("%s\n", buffer->data);
}

Application* application_new() {
  Application* application = malloc(sizeof(Application));
  return application;
}

void application_delete(Application* application) {
  free(application);
}

void application_launch(Application* application) {
}
