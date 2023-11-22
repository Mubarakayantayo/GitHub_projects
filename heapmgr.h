#ifndef HEAPMGR_H
#define HEAPMGR_H

/*
* purpose: allocated memory on the heap using headers and footers
* input:   size - the amount of space to be allocated (w/o header and footer)
* return:  a pointer to the start of the payload
*/
void *my_malloc(int size);

/*
* purpose: mark memory as unused and coellese ajacent blocks
* input:   memloc - pointer to payload of memory location to free
* return:  nothing
*/
void my_free(void *ptr);

/*
* purpose: Print out the heap
* inputs:  None
* return:  None (printing out to the screen is a side effect
*/
void print_heap();

#endif
