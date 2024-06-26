#include "template.h"

#include <stdlib.h> // exit()
#include <fcntl.h>  // fcntl(), F_GETFL, F_SETFL, O_NONBLOCK

void utility_setFDNonBlock(int fd) {
  int flags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void utility_exitIfMinusOne(int value) {
  if (value == -1) {
    perror("error ");
    exit(EXIT_FAILURE);
  }
}
