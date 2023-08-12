#include "dlinkedlist.h"
#include "stack.h"
#include <stdbool.h>

void push(DList *stack, int key){
    dlist_insert(stack, stack->head, key, NULL);
}

int pop(DList *stack){
    int result = stack->head->_next->key;
    dlist_remove(stack, stack->head->_next, false);
    return result;
}

bool is_empty(const DList *stack){
    return stack->head->_next == stack->tail;
}

