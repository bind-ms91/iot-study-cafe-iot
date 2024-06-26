#include "utility.h"

#include <stdio.h>  // perror()
#include <stdlib.h> // exit()
#include <fcntl.h>  // fcntl(), F_GETFL, F_SETFL, O_NONBLOCK
#include <termios.h>

void utility_fd_setNonBlock(int fd) {
  int flags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void utility_fd_setCanon(int fd) {
  struct termios termios;
  tcgetattr(fd, &termios);
  termios.c_lflag |= ICANON;
	tcsetattr(fd, TCSANOW, &termios);
}

void utility_exitIfMinusOne(int value) {
  if (value == -1) {
    perror("error ");
    exit(EXIT_FAILURE);
  }
}
