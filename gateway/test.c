#define TEST011

/*
#ifdef TEST000
#include <stdio.h>

int main() {
  return 0;
}
#endif
 */

#ifdef TEST011
// read serial port from FILE
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "buffer.h"

#define ARDUINO_FILE_PATH "/dev/cu.usbmodem1101"

void setFD(int fd) {
  int flags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);

  struct termios termios;
  termios.c_lflag |= ICANON;
	tcsetattr(fd, TCSANOW, &termios);
}

int main() {
  FILE* file = fopen(ARDUINO_FILE_PATH, "a");
  int fd = fileno(file);

//  int fd = open(ARDUINO_FILE_PATH, O_RDWR);
//  FILE* file = fdopen(fd, "a");

//  setFD(fd);

  Buffer* buffer = buffer_new();

  while (1) {
    fscanf(file, "%s%n\n", buffer->data, &buffer->count);
//    ssize_t numberRead = read(fd, buffer->data, buffer_defaultCapacity());
    write(1, buffer->data, buffer->count);
  }

  buffer_delete(buffer);

  return 0;
}
#endif

#ifdef TEST010
// read serial port from fd
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "buffer.h"

#define ARDUINO_FILE_PATH "/dev/cu.usbmodem1101"

void setFD(int fd) {
  int flags = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, flags | O_NONBLOCK);

  struct termios termios;
  tcgetattr(fd, &termios);
  termios.c_lflag |= ICANON;
	tcsetattr(fd, TCSANOW, &termios);
}

int main() {
  int fd = open(ARDUINO_FILE_PATH, O_RDWR);

  setFD(fd);

  Buffer* buffer = buffer_new();

  while (1) {
    ssize_t numberRead = read(fd, buffer->data, buffer_defaultCapacity());
    write(1, buffer->data, numberRead);
  }

  buffer_delete(buffer);

  return 0;
}
#endif

#ifdef TEST009
// read line of file test
#include <stdio.h>

int main() {
//  open file();
//  while (read line()) {
//    print();
//  }

  return 0;
}
#endif

#ifdef TEST008
// write to server socket test
// - Result : success
#include <stdio.h>
#include <unistd.h> // sleep()
#include <time.h> // time(), ctime()
#include <string.h> // strlne()

#include "file.h"

int main() {
  File* serverStream = file_newServerSocketStream("127.0.0.1", "4322");

  time_t currentTime;
  while (1) {
    time(&currentTime);
    char* timeString = ctime(&currentTime);
    write(file_fd(serverStream), timeString, strlen(timeString));
    sleep(1);
  }

  file_delete(serverStream);

  return 0;
}
#endif

#ifdef TEST007
// serial port read line test
#include <stdio.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "file.h"
#include "protocol_dht.h"
#include "buffer.h"

#define ARDUINO_FILE_PATH "/dev/cu.usbmodem1101"

void readWithSelect(File* file) {
  fd_set readFDSetReserve;
  fd_set readFDSet;
  int selectResult;
  Buffer* bufferToWriteToDBServer = buffer_new();
  int fd = file_fd(file);

  FD_ZERO(&readFDSetReserve);
  FD_SET(fd, &readFDSetReserve);

  while (1) {
    memcpy(&readFDSet, &readFDSetReserve, sizeof(fd_set));

    selectResult = select(FD_SETSIZE, &readFDSet, NULL, NULL, NULL);
    if (selectResult < 0) {
      perror("select() failed");
      exit(EXIT_FAILURE);
    }

    if (FD_ISSET(fd, &readFDSet)) {
      printf("ready to read\n");
      ssize_t readResult = read(fd, bufferToWriteToDBServer, 512);
      printf("readResult : %zd, bufferToWriteToDBServer : %s\n", readResult, bufferToWriteToDBServer->data);
      char* line = file_readLine(file);
      printf("from : %s\n", line);
      if (protocol_dht_isValid(line)) {
        printf("valid");
        buffer_copyAssign(bufferToWriteToDBServer, file->readLineBuffer);
      }
    }
  }

  buffer_delete(bufferToWriteToDBServer);
}

void backup(File* file) {
  char* line = NULL;

  while ((line = file_readLine(file)) != NULL) {
    printf("%s\n", line);
  }
}

int main() {
  File* arduinoFile = file_newSerialPort(ARDUINO_FILE_PATH);

  readWithSelect(arduinoFile);

  file_delete(arduinoFile);

  return 0;
}
#endif

#ifdef TEST006
#define TEST006
#include <stdio.h>  // getline()
#include <fcntl.h>  // open()

int main() {
  char* buffer = NULL;
  size_t capacity = 0;

  int configFileFD = open("config.ini", O_RDONLY);
  if (configFileFD == -1) {
    return -1;
  }

  FILE* configFileStream = fdopen(configFileFD, "r");

  while (getline(&buffer, &capacity, configFileStream) != -1) {
    printf("line : %s", buffer);
  }

  perror("[terminating] ");

  return 0;
}
#endif // TEST006

#ifdef TEST005
#include <stdio.h>
#include <fcntl.h>

int main() {
  char buffer[512];

  int configFileFD = open("config.ini", O_RDONLY);
  if (configFileFD == -1) {
    return -1;
  }

  FILE* configFileStream = fdopen(configFileFD, "r");

  while (fscanf(configFileStream, "%s\n", buffer) != -1) {
    printf("line : %s\n", buffer);
  }

  perror("[terminating] ");

  return 0;
}
#endif

#ifdef TEST004
#include "buffer.h"

#include <stdio.h>
#include <fcntl.h>

int main() {
  Buffer* buffer = buffer_new();
  int configFileFD = open("config.ini", O_RDONLY);

  while (buffer_readLine(buffer, configFileFD) != -1) {
    printf("%s\n", buffer->data);
  }

  perror("[terminating] ");

  return 0;
}
#endif

#ifdef TEST003
#include <stdio.h>
#include <sys/types.h>

ssize_t readLine(int fd, char* buffer) {
  ssize_t numberRead = read(configFile, buffer, BUFFER_SIZE - 1);
  if (numberRead != -1) {
    buffer[BUFFER_SIZE] = '\0';
  }

  return numberRead;
}

int main() {
  char buffer[BUFFER_SIZE];
  int configFileFD = open("config.ini", O_RDONLY);

  for (readLine(configFileFD, buffer)) {
    printf("line : %s", buffer);
  }

  perror("[terminating] ");

  return 0;
}
#endif
