#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace FD {

void setNonBlock(int fd);
void setCanon(int fd);

}

void exitIf(bool expression);

#endif  // UTILITY_HPP
