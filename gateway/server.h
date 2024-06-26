#ifndef SERVER_H
#define SERVER_H

typedef struct server {
  int listenSocketFD;
} Server;

//Server* server_new();
Server* server_new_listenPortNumber(const char* listenPortNumber);

void server_delete(Server* server);

int server_accept(Server* server);

#endif  // SERVER_H
