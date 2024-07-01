#ifndef APPLICATION_H
#define APPLICATION_H

typedef struct application {
  char* ipAddress;
  char* portNumber;
} Application;

Application* application_new();
void application_delete(Application* application);
void application_launch(Application* application);

#endif  // APPLICATION_H
