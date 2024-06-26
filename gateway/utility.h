#ifndef UTILITY_H
#define UTILITY_H

void utility_fd_setNonBlock(int fd);
void utility_fd_setCanon(int fd);
void utility_exitIfMinusOne(int value);

#endif  // UTILITY_H
