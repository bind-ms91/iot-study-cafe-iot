#include "Select.hpp"

#include <sys/select.h> // select();
#include <cstring>  // std::memcpy()
#include <algorithm>  // std::max()

#include "Utility.hpp"

Select::Select() {
  _nfds = 3;

  FD_ZERO(&_readFDSetReserve);
  FD_ZERO(&_writeFDSetReserve);
}

void Select::readFDSet_add(int fd) {
  FD_SET(fd, &_readFDSetReserve);

  if (fd >= _nfds) {
    _nfds = fd + 1;
  }
}

bool Select::readFDSet_isSet(int fd) const {
  return FD_ISSET(fd, &_readFDSet);
}

void Select::readFDSet_remove(int fd) {
  FD_CLR(fd, &_readFDSetReserve);
}

void Select::writeFDSet_add(int fd) {
  FD_SET(fd, &_writeFDSetReserve);

  if (fd >= _nfds) {
    _nfds = fd + 1;
  }
}

bool Select::writeFDSet_isSet(int fd) const {
  return FD_ISSET(fd, &_writeFDSet);
}

void Select::writeFDSet_remove(int fd) {
  FD_CLR(fd, &_writeFDSetReserve);
}

void Select::select() {
  std::memcpy(&_readFDSet, &_readFDSetReserve, sizeof(fd_set));
  std::memcpy(&_writeFDSet, &_writeFDSetReserve, sizeof(fd_set));

  const int selectResult = ::select(_nfds, &_readFDSet, &_writeFDSet, NULL, NULL);
  exitIf(selectResult == -1);
}
