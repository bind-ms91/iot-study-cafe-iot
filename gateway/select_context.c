#include "select_context.h"

#include <stdlib.h> // malloc(), free()
#include <sys/select.h>

#include "utility.h"

SelectContext* selectContext_new() {
  SelectContext* selectContext = malloc(sizeof(selectContext));

  FD_ZERO(&selectContext->readFDSetReserve);
  FD_ZERO(&selectContext->writeFDSetReserve);

  return selectContext;
}

void selectContext_delete(SelectContext* selectContext) {
  free(selectContext);
}

void selectContext_readFDSet_add(SelectContext* selectContext, int fd) {
  FD_SET(fd, selectContext->readFDSetReserve);
}

void selectContext_readFDSet_remove(SelectContext* selectContext, int fd) {
  FD_CLR(fd, selectContext->readFDSetReserve);
}

int selectContext_isSet(SelectContext* selectContext, int fd) {
  return FD_ISSET(fd, selectContext->readFDSet);
}

void selectContext_select(SelectContext* selectContext) {
  memcpy(&selectContext->readFDSet, &selectContext->readFDSetReserve, sizeof(fd_set));
  const int selectResult = select(FD_SETSIZE, &readFDSet, NULL, NULL, NULL);
  utility_exitIfMinusOne(selectResult);
}
