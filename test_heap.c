#include <stdio.h>
#include <stdlib.h>
#include "heapmgr.h"


void result(const char *exp, void (*test)()){
  
  printf("\n****%s****\n",exp);
  test();
  print_heap();
}

void test1(){
}

void test2(){
  void *ptr = my_malloc(1024*1024+1024);
  printf("ptr should be (nil) it is: %p\n",ptr);
}

void test3(){
  void *ptr = my_malloc(1024*1024-8);
  printf("ptr is: %p\n",ptr);
}

void test4(){
  void *ptr = my_malloc(1024*1024-8);
  my_free(ptr);
}

void test5(){
  void *ptr = my_malloc(1024*1024-16);
  printf("ptr is: %p\n",ptr);
}

void test6(){
  void *ptr = my_malloc(16);
  printf("ptr is: %p\n",ptr);
}


void test7(){
  void *ptr = my_malloc(16);
  printf("ptr is: %p\n",ptr);
  ptr = my_malloc(16);
  printf("new ptr is: %p\n",ptr);
}


void test8(){
  my_malloc(17);
}


void test9(){
  my_malloc(2);
}


void test10(){
  my_malloc(16);
  void *ptr2 = my_malloc(16);
  my_malloc(16);
  my_malloc(16);
  my_free(ptr2);
}


void test11(){
  my_malloc(16);
  void *ptr2 = my_malloc(16);
  my_malloc(16);
  my_malloc(16);
  my_free(ptr2);
  printf("Freed %p\n",ptr2);
  ptr2 = my_malloc(16);
  printf("Filled %p\n",ptr2);
}


void test12(){
  my_malloc(16);
  void *ptr2 = my_malloc(16);
  void *ptr3 = my_malloc(16);
  my_malloc(16);
  my_free(ptr2);
  my_free(ptr3);
}


void test13(){
  my_malloc(16);
  void *ptr2 = my_malloc(16);
  void *ptr3 = my_malloc(16);
  my_malloc(16);
  my_free(ptr2);
  my_free(ptr3);
  ptr2 = my_malloc(40);
}


void test14(){
  my_malloc(16);
  void *ptr2 = my_malloc(16);
  void *ptr3 = my_malloc(16);
  my_malloc(16);
  my_free(ptr3);
  my_free(ptr2);
}


void test15(){
  my_malloc(16);
  void *ptr2 = my_malloc(16);
  void *ptr3 = my_malloc(16);
  void *ptr4 = my_malloc(16);
  my_malloc(16);

  my_free(ptr2);
  my_free(ptr3);
  my_free(ptr4);
}


void test16(){
  test15();
  my_malloc(16);
}


void test17(){
  test15();
  my_malloc(72);
}


void test18(){
  my_malloc(16);
  void *ptr2=my_malloc(16);
  my_malloc(16);

  my_free(ptr2);
  my_malloc(8);
}


void test19(){
  void *ptr=my_malloc(32);
  ptr = my_malloc(1024*1024-16);
  printf("ptr should be (nil) it is: %p\n",ptr);
}


void test20(){
  my_free(NULL);
}

void test21(){
  void *ptr;
  my_malloc(1024*1024-8);
  ptr = my_malloc(32);
  printf("Pointer should be (nil): %p\n",ptr);
}

void test22(){
  int *array;
  array = (int *)my_malloc(4*sizeof(int));
  array[0]=0;
  array[1]=1;
  array[2]=2;
  array[3]=3;
  printf("array should be 0 1 2 3: %d, %d, %d, %d\n", array[0], array[1], array[2], array[3]);
}

void test23(){
  int *array;
  int *array2;

  array = (int *)my_malloc(4*sizeof(int));
  array[0]=0;
  array[1]=1;
  array[2]=2;
  array[3]=3;

  array2 = (int*)my_malloc(4*sizeof(int));
  array2[0]=5;
  array2[1]=6;
  array2[2]=7;
  array2[3]=8;

  printf("array should be 0 1 2 3: %d, %d, %d, %d\n", array[0], array[1], array[2], array[3]);
  printf("array2 should be 5 6 7 8: %d, %d, %d, %d\n", array2[0], array2[1], array2[2], array2[3]);
}

void test24(){
  int *array;
  array = (int*)my_malloc(4*sizeof(int));
  array[0]=5;
  array[1]=6;
  array[2]=7;
  array[3]=8;
  my_free(array);
}

void test25(){
  int *array;
  array = (int*)my_malloc(4*sizeof(int));
  array[0]=5;
  array[1]=6;
  array[2]=7;
  array[3]=8;
  my_free(array);
  array = (int*)my_malloc(4*sizeof(int));
  array[0]=10;
  array[1]=11;
  array[2]=12;
  array[3]=13;
  printf("array should be 10 11 12 13: %d, %d, %d, %d\n", array[0], array[1], array[2], array[3]);
}


static const char *names[]={
                            "Test print heap with an unused heap",
                            "Malloc too much with nothing used",
                            "Malloc the whole heap (i.e., no splitting)",
                            "Free one big block",
                            "Create block without room to split",
                            "Create block of multiple of 8. Split big block",
                            "Create a second block after the first",
                            "Create a block not on a double word",
                            "Create a block smaller than the min size",
                            "Free, case 1, nothing to coalesce",
                            "Reassign previously assigned block",
                            "Free, case 2, coaelse after",
                            "Fully use newly coalesced block (or not)",
                            "Free, case 3, coalesce before",
                            "Free, case 4, coalesce before and after",
                            "Split newly coalesced block",
                            "Skip over holes that are too small",
                            "Don't split if the hole is too small",
                            "Malloc too much with some used",
                            "Free NULL",
                            "Malloc on a full heap",
			    "Use the allocated space",
			    "allocate two arrays",
			    "Use the space and then free",
			    "Use the space, free, allocate again"
                           };

void (*tests[])()={test1,test2,test3,test4,test5,test6,test7,test8,test9,
                   test10,test11,test12,test13,test14,test15,test16,test17,
                   test18,test19,test20,test21,test22,test23,test24,test25};

int main(int argc, char *argv[]){

  int testnum;  

  if(argc < 2){
    printf("Usage: %s testnumber\n",argv[0]);
    printf("\tmin testnum is 1, max is %lu\n",sizeof(names)/sizeof(char*));
    exit(0);
  }

  if(sscanf(argv[1],"%d",&testnum) < 1){
    printf("Invalid test number\n");
    exit(-1);
  }

  if(testnum < 1 || testnum > sizeof(names)/sizeof(char*)){
    printf("Invalid test number\n");
    exit(-1); 
  }

  result(names[testnum-1],tests[testnum-1]);


}
