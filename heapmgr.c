#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static const int MAX_HEAP = 1024*1024;
static const int MIN_SIZE = 8;

/* 
* purpose: Ensure the intialization of the heap to be managed
* input:   None
* return:  The start of the heap
*/
static void *get_heap(){
 
  int *header;
  static void* start=0;
    
  //if we have a heap already, great, return the front of it
  if (start != 0){
    return start;
  }

  //allocate MAX_HEAP bytes for our heap manager by moving the break
  if ( (start = sbrk(MAX_HEAP+4)) <0){
    perror("sbrk");
    return NULL;
  }
  //payloads need to be on an 8 byte boundry and the headers are 4, so...
  start+=4;
  
    //set the header for the whole big chunk (ignoring a prologue)
  header=start;
  *header = MAX_HEAP;

  //set the footer for the whole big chunk (ignoring an epilogue)
  header = sbrk(0);
  *(header-1)=MAX_HEAP;      

  return start;
}

/*
* purpose: allocated memory on the heap using headers and footers
* input:   size - the amount of space to be allocated (w/o header and footer)
* return:  a pointer to the begining of the payload
*/



void *my_malloc(unsigned int size) {
// Initialize the heap if it hasn't been already
    static void *heap_start = 0;
    if (heap_start == 0) {
        heap_start = get_heap();
    }

    /* Calculate the total size required for the payload and align to an 8-byte boundary */
    int total_size = (size + MIN_SIZE - 1 + 7) & -8;

    // Start at the beginning of the heap and iterate over each block
    void *curr = heap_start;
    while (curr < sbrk(0)) {
        // Get the size of the current block
        int *header = curr;
        int block_size = *header & ~1;  // use bitwise AND to get the block size ignoring the last bit

        // If the block is free and big enough for the payload, use it
        if ((block_size & 1) == 0 && block_size >= total_size) {
            // split the block if there is enough space for a new block
            if (block_size > total_size + 2 * MIN_SIZE) {
                // Set the header for the new block
                int *new_header = curr + total_size;
                *new_header = (block_size - total_size - 2 * MIN_SIZE) | 1;  // use bitwise OR to make the block size odd

                // Set the footer for the new block
                int *new_footer = new_header + (*new_header / 4) - 1;
                *new_footer = *new_header;

                // Set the header for the remaining block
                *header = (total_size << 1) | 1;  // use left shift to multiply by 2 and bitwise OR to make the block size odd

                // Set the footer for the remaining block
                int *footer = header + (block_size / 4) - 1;
                *footer = *header;

                return header + 1;
            } else {
                // Use the entire block for the payload
                *header |= 1;  // set the last bit to 1 to mark the block as used

                // Set the footer for the block
                int *footer = header + (block_size / 4) - 1;
                *footer = *header;

                return header + 1;
            }
        }

        // Move to the next block
        curr += block_size;
    }

    // If there is no block that can fit the payload, return NULL
    printf("unable to successfully allocate memory\n");
    return NULL;
}




/*
* purpose: mark memory as unused and coellese ajacent blocks
* input:   memloc - pointer to payload of memory location to free
* return:  nothing
*/ 

void my_free(void *memloc) {
	int *header = (int *) memloc - 1;
	int *footer = (int *) (((char *) header) + (*header * 2) - 4);
	// Mark header as free (lowest bit set to 0)
		*header &= ~1;
	// Check if previous block is free
	int *prev_footer = header - 1;
	if (*prev_footer % 2 == 0) {
		int *prev_header = (int *) (((char *) prev_footer) - (*prev_footer - 4));
		*prev_header += *header;
		header = prev_header;
	}
	// Check if next block is free
	int *next_header = footer + 1;
	if (*next_header % 2 == 0) {
		int *next_footer = (int *) (((char *) next_header) + (*next_header * 2) - 4);
		*header += *next_header;
		*next_footer += *header - *next_header;
		footer = next_footer;
	}
	// Mark footer as free (lowest bit set to 0)
	*footer &= ~1;
}









/*
* purpose: Print out the heap
* inputs:  None
* return:  None (printing out to the screen is a side effect
*/
void print_heap() {
    // Get the heap starting address
    void *curr = get_heap();
    
    // Initialize the block count
    int block_num = 1;
    
    // Iterate over each block on the heap and print the header
    while (curr < sbrk(0)) {
        // Get the size and status of the block from the header
        int *header = curr;
        int block_size = *header;
        int is_used = block_size % 2; // If header is odd, block is used, otherwise it's free
        
        if (is_used) {
            block_size = block_size - 1; // Subtract 1 to get the actual block size
        }
        
        // Print the header information for the block
        printf("Block %d: Header=%p, Size=%d bytes, %s\n", block_num, header, block_size, is_used ? "Used" : "Free");
        
        // Move to the next block
        curr += block_size;
        block_num++;
    }
}
