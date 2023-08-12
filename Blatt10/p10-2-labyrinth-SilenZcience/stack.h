#ifndef CA_STACK_H_
#define CA_STACK_H_

#include "dlinkedlist.h"
#include <stdbool.h>

void push(DList *stack, Position key);
Position pop(DList *stack);
bool is_empty(const DList *stack);

#endif
