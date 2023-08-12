#ifndef CA_ILIST_H_
#define CA_ILIST_H_

#define dl_init_element(x) { \
    (x)->prev = NULL; \
    (x)->next = NULL; \
};

#define dl_insert(p, x) { \
    (x)->prev = p; \
    (x)->next = (p)->next; \
    (p)->next = x; \
    if((x)->next) (x)->next->prev = x; \
};

#define dl_remove(x) { \
    if((x)->prev) (x)->prev->next = (x)->next; \
    if((x)->next) (x)->next->prev = (x)->prev; \
};

#define forall_elements(x) for(; (x) != NULL; x = (x)->next)

#endif
