#include "dlinkedlist.h"
#include "stack.h"
#include <stdbool.h>

void push(DList *stack, Position key){
    dlist_insert(stack, stack->head, key, NULL);
}

Position pop(DList *stack){
    Position result = stack->head->_next->key;
    dlist_remove(stack, stack->head->_next, false);
    return result;
}

bool is_empty(const DList *stack){
    return stack->head->_next == stack->tail;
}

