#include <stdio.h>  // printf(), perror()
#include <stdlib.h> // EXIT_FAILURE
#include <unistd.h> // close()
#include <sys/select.h> // select()
#include <string.h> // memcpy()

#include "application.h"

#define ARDUINO_FILE_PATH "/dev/cu.usbmodem1101"

//void selectLoop() {
//  File* arduinoFile = file_newSerialPort(ARDUINO_FILE_PATH);
//  File* dbServerFile = file_newServerSocketStream("127.0.0.1", "4322");
//
//  int arduinoFD = file_fd(arduinoFile);
////  int dbServerFD = file_fd(dbServerFile);
//
//  fd_set readFDSetReserve;
//  fd_set readFDSet;
//
//  fd_set writeFDSetReserve;
//  fd_set writeFDSet;
//
//  int selectResult;
//
//  FD_ZERO(&readFDSetReserve);
//  FD_SET(arduinoFD, &readFDSetReserve);
//
//  FD_ZERO(&writeFDSet);
////  FD_SET(dbServerFD, &writeFDSet);
//  // must use writeFDSetReserve
//
//  fd_set* readfds = &readFDSet;
//  fd_set* writefds;
//
//  Buffer* bufferToWriteToDBServer = buffer_new();
//
//  while (1) {
//    memcpy(&readFDSet, &readFDSetReserve, sizeof(fd_set));
//    writefds = buffer_isEmpty(bufferToWriteToDBServer) ? NULL : &writeFDSet;
//
//    selectResult = select(FD_SETSIZE, &readFDSet, writefds, NULL, NULL);
//    printf("selected\n");
//
//    if (selectResult < 0) {
//      perror("select() failed");
//      exit(EXIT_FAILURE);
//    }
//
//    if (FD_ISSET(arduinoFD, &readFDSet)) {
//      printf("ready to read\n");
//      char* line = file_readLine(arduinoFile);
//      printf("from : %s\n", line);
//      if (protocol_dht_isValid(line)) {
//        printf("valid");
//        buffer_copyAssign(bufferToWriteToDBServer, arduinoFile->readLineBuffer);
//      }
//    }
//    else if (writefds != NULL) {
//      if (0) {
////      if (FD_ISSET(dbServerFD, writefds)) {
//        printf("to : %s\n", bufferToWriteToDBServer->data);
////        write(dbServerFD, bufferToWriteToDBServer->data, bufferToWriteToDBServer->count);
//        buffer_clear(bufferToWriteToDBServer);
//      }
//    }
//  }
//
//  file_delete(arduinoFile);
//  buffer_delete(bufferToWriteToDBServer);
////  file_delete(dbServerFile);
//}

int main() {
  Application* application = application_new();
  application_launch(application);
  application_delete(application);

  return 0;
}
