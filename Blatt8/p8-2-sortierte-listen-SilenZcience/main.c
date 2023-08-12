#include "io.h"
#include "mergesort.h"
#include "dlinkedlist.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    DList* input = read_input(stdin);
    merge_sort_bottom_up(input);

    dlist_print(input, stdout);
    dlist_destroy(input);


    return 0;
}
