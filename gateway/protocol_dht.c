#include "protocol_dht.h"

#include <stdio.h>  //sscanf()
#include <sys/types.h>  // ssize_t

int protocol_dht_isValid(char* buffer) {
  float temperature;
  float humidity;
  ssize_t numberAssigned = sscanf(buffer, "{\"temperature\":%f,\"humidity\":%f}\n", &temperature, &humidity);

  return numberAssigned == 2;
}
