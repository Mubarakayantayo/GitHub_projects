#include <stdlib.h>
#include <stdio.h>

#include "card.h"
#include "cardlist.h"
#include "heapmgr.h"


/*
* purpose : create a new circularly linked list_t
* input   : None
* returns : An intitalized circularly linked list_t
*/  
list_t list_create(){

  return NULL;
}

/* 
* purpose : create a new node_t with a link, a private function
* input   : new_card_t - the card_t to insert into the node_t
*           next     - the node_t to link this one to. Links to itself if NULL
* return  : a new node_t for the list_t
*/
static node_t* node_t_create(card_t new_card_t, node_t *next){
  node_t *new_node_t = (node_t *) my_malloc(sizeof(node_t));
  if (new_node_t == NULL){
    perror("malloc");
    return NULL;
  }

  new_node_t->data=new_card_t;

  //make this node_t circular instead of defaulting to NULL
  if (next != NULL){
    new_node_t->next=next;
  } else {
    new_node_t->next=new_node_t;
  }

  return new_node_t;
}

/*
* purpose : add a card_t to the start of the list_t
* input   : list_t - a pointer to the list_t to add to
*           new_card_t - the card_t to add to the list_t
* return  : 1 if successful
*/
int list_add_start(list_t *list_t, card_t new_card_t){

  if (*list_t == NULL){

    //The list_t is empty, so the node_t we create is the whole thing
    *list_t = node_t_create(new_card_t,*list_t);
    
    if (*list_t == NULL){
      return 0;
    }

  } else {

    //The list_t has an element, so go to the begining and add it there
    (*list_t)->next = node_t_create(new_card_t, (*list_t)->next);
    
    if ((*list_t)->next == NULL){
      return 0;
    }
  }

  return 1;
}

/*
* purpose : Add a node_t to the end of the list_t
* input   : list_t - a pointer to the list_t to add to
*           new_card_t - the card_t to add
* return  : 1 if successful.
*/
int list_add_end(list_t *list_t, card_t new_card_t){

  // in a circularly linked list_t, adding to the end is the same as
  // adding to the begining, but you shift where you point
  if (list_add_start(list_t, new_card_t) == 1){
    *list_t=(*list_t)->next;  
    return 1;
  } else {
    return 0;
  }
}

/*
* purpose : Find a card_t in the list_t
* input   : list_t - the list_t to search
*           needle - the card_t to find
* return  : the card_t found or INVALID_card_t
*/
card_t list_find(list_t list_t, card_t needle){

  node_t *curr;
  if (list_t == NULL)
      return INVALID_CARD;;
  
  // start at the begining and go till you get back to the end
  for( curr=list_t->next; curr != list_t; curr = curr->next){
    if(card_compare(curr->data,needle)==0){
      return curr->data;
    }
  }

  //if you get to the end, check if it's the one
  if(card_compare(curr->data,needle)==0){
      return curr->data;
  }
  
  return INVALID_CARD;
}

/*
* purpose : delete the searched or card_t
* input   : list_t   - a pointer to the list_t to delete from
*           needle - the card_t to delete
* return  : none
*/
void list_delete(list_t *list_t, card_t needle){

  node_t *prev=*list_t;
  node_t *curr;

  if (*list_t == NULL){
    return;
  }

  //in a circularly link list_t, start at the start and go till the end
  for( curr=(*list_t)->next; curr != *list_t; curr = curr->next){
    
    if(card_compare(curr->data,needle)==0){
      break;
    }
    prev = curr;
  }

  //once you have wrapped around, check if the end is the one
  if (curr == *list_t && card_compare(curr->data,needle)!=0){
    return;
  }

  
  if (prev == curr){
    //this was the last item in the list_t
    *list_t=NULL;
  } else {
    //remove the one we found 
    prev->next=curr->next;
  }

  if (curr == *list_t){
    //if we removed the last item in the list_t, shuft the tail pointer back
    *list_t=prev;
  }

  my_free(curr);
  
}

/*
* purpose : free the list_t
* input   : list_t - a pointer to the list_t to free
* return  : none
*/
void list_free(list_t *list_t){
  node_t *prev=*list_t;
  node_t *curr;  

  if (*list_t == NULL){
    return;
  }

  //start at the start and go to the end in a circular list_t
  for( curr=(*list_t)->next; curr != *list_t; curr = curr->next){
    my_free(prev);
    prev = curr;
  }

  my_free(prev);

}

/*
* purpose : print out all the card_ts in the list_t
* input   : list_t - the list_t to print
* return  : nothing (printing to the screen is a side effect)
*/
void list_print(list_t list_t){
  node_t *curr;  

  if (list_t == NULL){
    return;
  }

  //start at the start and go to the end in a circular list_t
  for( curr=list_t->next; curr != list_t; curr = curr->next){
    card_print(curr->data);
    printf(",");
  }

  card_print(curr->data);
}
