#ifndef CARDLIST_H
#define CARDLIST_H

#include "card.h"

typedef struct node_s{
  card_t data;
  struct node_s* next;
} node_t;

typedef node_t* list_t;

list_t list_create();
int list_add_start(list_t *list, card_t new_card);
int list_add_end(list_t *list, card_t new_card);
card_t list_find(list_t list, card_t needle);
void list_delete(list_t *list, card_t to_delete);
void list_free(list_t *list);
void list_print(list_t list);

#endif
