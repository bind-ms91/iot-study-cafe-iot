#include <stdio.h>  // printf()
#include <stdlib.h> // EXIT_FAILURE
#include <string.h> // memset()
#include <fcntl.h>  // open()
#include <unistd.h> // close()
#include <sys/time.h> // struct timeval

#define FILE_PATH "/dev/cu.usbmodem1101"
#define READ_BUFFER_SIZE 512

int main() {
  int arduinoFD = open(FILE_PATH, O_RDONLY);

  char readBuffer[READ_BUFFER_SIZE];
  fd_set readFDSet;
  fd_set eventFDSet;
  int selectResult;
  struct timeval timeout;
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;

  FD_ZERO(&readFDSet);
  FD_SET(arduinoFD, &readFDSet);

  while (1) {
    eventFDSet = readFDSet;
    selectResult = select(FD_SETSIZE, &eventFDSet, NULL, NULL, &timeout);

    if (selectResult < 0) {
      fprintf(stderr, "%s : select() failed", __func__);
      return EXIT_FAILURE;
    }

    if (!FD_ISSET(arduinoFD, &eventFDSet)) {
      continue;
    }

    ssize_t readBytes = read(arduinoFD, readBuffer, READ_BUFFER_SIZE);
    if (readBytes > 0) {
      write(1, readBuffer, readBytes);
    }
  }

  close(arduinoFD);

  return 0;
}
