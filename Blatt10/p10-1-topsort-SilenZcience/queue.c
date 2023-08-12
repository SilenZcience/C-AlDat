#include "dlinkedlist.h"
#include "queue.h"
#include <stdbool.h>

void enqueue(DList *queue, int key){
    dlist_insert(queue, queue->head, key, NULL);
}

int dequeue(DList *queue){
    int result = queue->tail->_prev->key;
    dlist_remove(queue, queue->tail->_prev, false);
    return result;
}

bool is_empty(const DList *queue){
    return queue->head->_next == queue->tail;
}
