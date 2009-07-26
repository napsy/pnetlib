#ifndef __PNET_LIST_H__
#define __PNET_LIST_H__

struct pnet_list_s {
    struct pnet_list_s *next, *prev;
    void *data;
};

typedef struct pnet_list_s pnet_list_t;

pnet_list_t *
pnet_list_append(pnet_list_t *list, void *data);

void
pnet_list_remove(pnet_list_t *list,
                 int index);

int
pnet_list_size(pnet_list_t *list);

#endif

