Goals

Gain comfort in working with pointers
Understand the tasks that malloc and free and doing for you
Build a simple, but functional, memory manager
Problem

Now that you have built your linked list of cards, it's time to take it one step further. You boss (grump that he is) doesn't trust malloc and free to handle memory management, and insists that you can do better.

Analysis

He wants you to write void* my_malloc(unsigned int size) and void my_free(void *ptr) to replace the built-in versions of malloc and free. He has provided you a chunk of memory to manage and you don't have to worry about growing that chunk if you run out of space. (my_malloc should just return NULL if you run out of space).

Everything you need is in heapmgr.c. You only need to work on my_malloc, my_free.

In addition, you must write void print_heap() that will print out the location and size of each block and whether that block is used or free. (Hint: Do this early, it will help with the rest of the project.)

You are welcome to add other helper functions as you see fit.

Design

Usually, you would have to come up with the design on your own. However, this time a few things have been decided for you:

You will use an implicit free list.
Your memory must be double word aligned (A word is 4 bytes).
You solution must include BOTH a header and a footer.
Hint: Start with a version with just a header then make improvment.
You should perform immediate coalescing.
Hint: Do this last, or don't for a minor point reduction
Testing

Two files, solution.o and nocoalesce.o are available as given solutions. The Makefile will compile these against the test file for you and you can compare your solution against mine. Additionally, there is a solution to PA3 that that calls my_malloc and my_free so that you can test that it works in "production" code as well.

Final Submission

Submit to GitHub:

Your code (without derivable files)
A Makefile with targets heapmgr.o and clean as well as testheap that will run a test program to test your code (this may just use the .o file I have provided you).
A file, heapdump.txt that contains a dump of your heap after running your test program.
A set of milestones in milestone.txt that decribes how you broke up the problem.
A reflection addressing:
What was the most difficult part of this project?
Does tihs project give you any insight into how malloc behaves?
Do you understand memory any better, or was this just too in the weeds?
