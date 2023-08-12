#include "dlinkedlist.h"
#include "queue.h"

#include <stdbool.h>

Position dequeue(DList *queue){
    Position result = queue->tail->_prev->key;
    dlist_remove(queue, queue->tail->_prev, false);
    return result;
}

void enqueue(DList *queue, Position key){
    dlist_insert(queue, queue->head, key, NULL);
}

bool is_empty(const DList *queue){
    return queue->head->_next == queue->tail;
}
