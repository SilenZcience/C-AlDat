#ifndef CA_eiswagen_LIST_H_
#define CA_eiswagen_LIST_H_

#include "dlinkedlist.h"

typedef struct Junction {
    int ID;
    DList *streets;
} Junction;

void junction_init(Junction *j, int ID);

void junction_destroy(Junction *j);

#endif
