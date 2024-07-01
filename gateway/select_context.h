#ifndef SELECT_CONTEXT_H
#define SELECT_CONTEXT_H

#include <sys/select.h>

typedef struct selectContext {
  fd_set readFDSetReserve;
  fd_set readFDSet;

  fd_set writeFDSetReserve;
  fd_set writeFDSet;
} SelectContext;

SelectContext* selectContext_new();

void selectContext_delete(SelectContext* selectContext);

void selectContext_readFDSet_add(SelectContext* selectContext, int fd);
void selectContext_readFDSet_remove(SelectContext* selectContext, int fd);
int selectContext_isSet(SelectContext* selectContext, int fd);

void selectContext_select(SelectContext* selectContext);

#endif  // SELECT_CONTEXT_H
