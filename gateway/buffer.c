#include "buffer.h"

#include <stdio.h>  // scanf()
#include <stdlib.h> // malloc(), free()
#include <string.h> // memset(), memcpy()
#include <unistd.h> // read()
#include <stddef.h> // size_t
#include <sys/param.h>  // MIN()

#define DEFAULT_BUFFER_CAPACITY 512

size_t buffer_defaultCapacity() {
  return DEFAULT_BUFFER_CAPACITY;
}

Buffer* buffer_new() {
  return buffer_new_capacity(DEFAULT_BUFFER_CAPACITY);
}

Buffer* buffer_new_capacity(size_t capacity) {
  Buffer* buffer = malloc(sizeof(Buffer));

  char* data = malloc(sizeof(char) * capacity);
  memset(buffer, 0, sizeof(char) * capacity);
  buffer->data = data;

  buffer->capacity = capacity;

  return buffer;
}

void buffer_delete(Buffer* buffer) {
  free(buffer->data);
  free(buffer);
}

void buffer_copyAssign(Buffer* buffer, Buffer* rhs) {
  int count = MIN((int)buffer->capacity - 1, rhs->count);
  memcpy(buffer->data, rhs->data, count);
  buffer->count = count;
  buffer->data[buffer->count] = '\0';
}

int buffer_isEmpty(Buffer* buffer) {
  return buffer->count == 0;
}

int buffer_read(Buffer* buffer, int fildes) {
  buffer->count = read(fildes, buffer->data, buffer->capacity - 1);

  if (buffer->count != -1) {
    buffer->data[buffer->count] = '\0';
  }

  return buffer->count;
}

//// - Assume : numberRead <= buffer->capacity - 1
//int buffer_readLine(Buffer* buffer, int fildes) {
//  FILE* file = fdopen(fildes, "r");
//  ssize_t numberAssign = fscanf(file, "%s%n\n", buffer->data, &buffer->count);
//  if (buffer->count != -1) {
//    buffer->data[buffer->count] = '\0';
//  }
//
//  return buffer->count;
//}

void buffer_clear(Buffer* buffer) {
  buffer->count = 0;
  buffer->data[buffer->count] = '\0';
}
