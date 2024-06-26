#include "file.h"

#include <stdlib.h> // malloc(), free(), NULL
#include <fcntl.h>  // open()
#include <termios.h>  // struct termios, tcgetattr(), tcsetattr(), ICANON, TCSANOW
#include <string.h> // memset()
#include <arpa/inet.h>  // struct socketaddr_in
#include <sys/types.h>  // ssize_t

#include "buffer.h"
#include "utility.h"

FILE* _newSerialPortStream(const char* path) {
  FILE* file = fopen(path, "a+");
  if (file == NULL) {
    perror("_newSerialPortStream() ");
    return NULL;
  }

  int fd = fileno(file);

  utility_fd_setNonBlock(fd);
  utility_fd_setCanon(fd);

  return file;
}

File* file_newSerialPort(const char* path) {
  File* file = malloc(sizeof(File));

  file->stream = _newSerialPortStream(path);
  file->readLineBuffer = buffer_new();

  return file;
}

int _connectServerSocket(const char* ipAddress, const char* portNumber) {
  struct sockaddr_in serverSocketInetAddress;

  int serverSocketFD = socket(PF_INET, SOCK_STREAM, 0);
  if (serverSocketFD == -1) {
    return -1;
  }

  const unsigned long serverInetAddress = inet_addr(ipAddress);
  const uint16_t serverPortNumber = htons(atoi(portNumber));

  memset(&serverSocketInetAddress, 0, sizeof(serverSocketInetAddress));
  serverSocketInetAddress.sin_family = AF_INET;
  serverSocketInetAddress.sin_addr.s_addr = serverInetAddress;
  serverSocketInetAddress.sin_port = serverPortNumber;

  const int connectResult = connect(serverSocketFD, (struct sockaddr*)&serverSocketInetAddress, sizeof(serverSocketInetAddress));
  if (connectResult == -1) {
    return -1;
  }

  return serverSocketFD;
}

FILE* _newServerSocketStream(const char* ipAddress, const char* portNumber) {
  int serverSocketFD = _connectServerSocket(ipAddress, portNumber);
  if (serverSocketFD == -1) {
    perror("_newServerSocketStream()");
    exit(EXIT_FAILURE);
  }

  utility_fd_setNonBlock(serverSocketFD);

  FILE* serverSocketStream = fdopen(serverSocketFD, "a");
  return serverSocketStream;
}

File* file_new_fd(int fd, const char* mode) {
  File* file = malloc(sizeof(File));

  FILE* stream = fdopen(fd, mode);

  file->stream = stream;
  file->readLineBuffer = buffer_new();

  return file;
}

File* file_newServerSocketStream(const char* ipAddress, const char* portNumber) {
  File* file = malloc(sizeof(File));

  file->stream = _newServerSocketStream(ipAddress, portNumber);
  file->readLineBuffer = buffer_new();

  return file;
}

void file_delete(File* file) {
  fclose(file->stream);
  buffer_delete(file->readLineBuffer);
  free(file);
}

char* file_readLine(File* file) {
  ssize_t numberRead = getline(&file->readLineBuffer->data, &file->readLineBuffer->capacity, file->stream);
  if (numberRead == -1) {
    perror("file_getline()");
    printf("  stream : %p\n", file->stream);
    printf("  fd : %d\n", fileno(file->stream));
    exit(EXIT_FAILURE);
  }
  else {
    file->readLineBuffer->count = numberRead;
    return file->readLineBuffer->data;
  }
}
