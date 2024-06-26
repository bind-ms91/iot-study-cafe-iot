#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h> // size_t

typedef struct buffer {
  char* data;
  size_t capacity;
  int count;
} Buffer;

size_t buffer_defaultCapacity();

Buffer* buffer_new();
// - Assume : capacity != 0
Buffer* buffer_new_capacity(size_t capacity);

void buffer_delete(Buffer* buffer);

void buffer_copyAssign(Buffer* buffer, Buffer* rhs);

int buffer_isEmpty(Buffer* buffer);

int buffer_read(Buffer* buffer, int fildes);
//int buffer_readLine(Buffer* buffer, int fildes);

void buffer_clear(Buffer* buffer);

#endif  // BUFFER_H
