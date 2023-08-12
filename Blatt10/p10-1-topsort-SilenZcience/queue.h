#ifndef CA_QUEUE_H_
#define CA_QUEUE_H_

#include "dlinkedlist.h"
#include <stdbool.h>

int dequeue(DList *queue);
void enqueue(DList *queue, int key);
bool is_empty(const DList *queue);

#endif
