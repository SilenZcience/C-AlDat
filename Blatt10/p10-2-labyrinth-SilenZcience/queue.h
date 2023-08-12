#ifndef CA_QUEUE_H_
#define CA_QUEUE_H_

#include "labyrinth.h"

#include "dlinkedlist.h"
#include <stdbool.h>

Position dequeue(DList *queue);
void enqueue(DList *queue, Position key);
bool is_empty(const DList *queue);

#endif
