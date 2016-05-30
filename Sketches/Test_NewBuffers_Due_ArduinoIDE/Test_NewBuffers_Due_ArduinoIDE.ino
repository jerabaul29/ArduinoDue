// number of bits available ---------------------------------------
int available_bits = 0;
// -----------------------------------------------------------------


// for estimate of free memory -------------------------------------
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

extern char _end;
extern "C" char *sbrk(int i);
char *ramstart=(char *)0x20070000;
char *ramend=(char *)0x20088000;
// -----------------------------------------------------------------

void setup() {
 Serial.begin(115200);

 // estimate memory use --------------------------------------------
 char *heapend=sbrk(0);
 register char * stack_ptr asm ("sp");
  struct mallinfo mi=mallinfo();
  printf("\nDynamic ram used: %d\n",mi.uordblks);
  printf("Program static ram used %d\n",&_end - ramstart);
  printf("Stack ram used %d\n\n",ramend - stack_ptr);
  printf("My guess at free mem: %d\n",stack_ptr - heapend + mi.fordblks);

}

void loop(){

  delay(800);
  Serial.println(Serial.available());

}

