#include <stdlib.h>

#include "pnet-list.h"

pnet_list_t *
pnet_list_append(pnet_list_t *list,
                 void *data)
{
    pnet_list_t *item, *tmp = list;

    item = malloc(sizeof(*list));

    if (!list) {
        list = item;
        list->prev = NULL;
    } else {
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = item;
        item->prev = tmp;
    }

    item->next = NULL;
    item->data = data;

    return list;
}

void
pnet_list_remove(pnet_list_t *list,
                 int index)
{
}

int
pnet_list_size(pnet_list_t *list)
{
    pnet_list_t *tmp = list;

    if (!tmp)
        return 0;

    int size = 0;

    for (; tmp; size++, tmp = tmp->next);

    return size;
}

