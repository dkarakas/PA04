#include<stdio.h>


int main(){
  int integer = 0;
  //integer = integer>>5<<5;
  unsigned int mask = 1 << (8*4-1);
  int i;
  for(i = 0; i < 8*4; i++){
    int result = mask & integer;
    if(i%4 == 0)
      printf(" ");
    if(result == 0)
      printf("0");
    if(result != 0)
      printf("1");
    mask = mask >> 1;
  }
  printf("\n");
  return 1;
}

