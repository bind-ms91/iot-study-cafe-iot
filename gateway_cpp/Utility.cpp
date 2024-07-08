#include "Utility.hpp"

#include <cstdio>  // std::perror()
#include <cstdlib> // std::exit()
#include <fcntl.h>  // fcntl()
#include <termios.h>  // struct termios

void FD::setNonBlock(int fd) {
  int flags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void FD::setCanon(int fd) {
  struct termios termios;
  tcgetattr(fd, &termios);
  termios.c_lflag |= ICANON;
	tcsetattr(fd, TCSANOW, &termios);
}

void exitIf(bool expression) {
  if (expression) {
    std::perror("error ");
    std::exit(EXIT_FAILURE);
  }
}
