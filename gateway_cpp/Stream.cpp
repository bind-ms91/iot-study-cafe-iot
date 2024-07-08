#include "Stream.hpp"

#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#include "Utility.hpp"

Stream::Stream(int fd)
: _fd(fd), _writeCount(0)
{
}

const std::string& Stream::readBuffer() const {
  return _readBuffer;
}

void Stream::appendWriteBuffer(const std::string& string) {
  _writeBuffer += string;
}

ssize_t Stream::read() {
  char buffer[512 + 1];

  ssize_t numberRead = ::read(_fd, buffer, 512);
  if (numberRead == -1) {
    return -1;
  }

  buffer[numberRead] = '\0';

  _readBuffer = _readBuffer + buffer;

  return numberRead;
}

ssize_t Stream::write() {
  ssize_t numberWrite = ::write(_fd, _writeBuffer.c_str(), _writeBuffer.length());
  if (numberWrite == -1) {
    return -1;
  }

  _writeCount += numberWrite;
  if (_writeCount == _writeBuffer.length()) {
    _writeBuffer.clear();
    _writeCount = 0;
  }

  return numberWrite;
}
