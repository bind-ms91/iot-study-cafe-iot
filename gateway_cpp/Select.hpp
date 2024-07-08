#ifndef SELECT_HPP
#define SELECT_HPP

#include <sys/select.h>

class Select {

public :
  Select();

  void readFDSet_add(int fd);
  bool readFDSet_isSet(int fd) const;
  void readFDSet_remove(int fd);

  void writeFDSet_add(int fd);
  bool writeFDSet_isSet(int fd) const;
  void writeFDSet_remove(int fd);

  void select();


private :
  int _nfds;

  fd_set _readFDSetReserve;
  fd_set _readFDSet;

  fd_set _writeFDSetReserve;
  fd_set _writeFDSet;

};

#endif  // SELECT_HPP
