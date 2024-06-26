#ifndef FILE_H
#define FILE_H

#include <stdio.h>  // FILE, fileno()

#include "buffer.h"

typedef struct file {
  FILE* stream;
  Buffer* readLineBuffer;
} File;

//File* file_new();
File* file_newSerialPort(char* path);
//File* file_new_fd_mode(int fd, char* mode);
File* file_newServerSocketStream(const char* ipAddress, const char* portNumber);

void file_delete(File* file);

static inline int file_fd(File* file) { return fileno(file->stream); }

char* file_readLine(File* file);

#endif  // FILE_H
