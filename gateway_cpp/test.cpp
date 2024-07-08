#define TEST_CASE004

#ifdef TEST_CASE000
// test case template
int main() {

  return 0;
}
#endif

#ifdef TEST_CASE004
// test Stream read write
#include <fcntl.h>

#include "Stream.hpp"

int main() {
  int inputFD = open("input.txt", O_RDONLY);
  int outputFD = open("output.txt", O_WRONLY);

  Stream inputStream = Stream(inputFD);
  Stream outputStream = Stream(outputFD);

  inputStream.read();
  printf("read line : %s\n", inputStream.readBuffer.c_str());

  outputStream.writeBuffer = "hi, there\n";
  outputStream.write();

  return 0;
}
#endif

#ifdef TEST_CASE003
// test Utility.hpp namespace
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "Utility.hpp"

int main() {
  char buffer[512];

  int input = open("input.txt", O_RDONLY);
  FD::setCanon(input);

  ssize_t numberRead = read(input, buffer, 512);
  buffer[numberRead] = '\0';

  printf("line : %s\n", buffer);

  return 0;
}
#endif
