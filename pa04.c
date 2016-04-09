#include<stdio.h>
#include<stdlib.h>
#include"answer04.h"


int main(int argc, char**argv) {
  if(argc != 5)
    return EXIT_FAILURE;
  //VARIABLES
  long int weight[256] = {0};
  FILE *fptr = fopen(argv[1],"r");
  if(fptr == NULL){
    fprintf(stderr,"failed to open file input");
    return EXIT_SUCCESS;
  }else if(fgetc(fptr) != EOF){ 
    FILE *out_fptr = fopen(argv[2],"w");
    if(out_fptr == NULL){
      fprintf(stderr,"failed to open file output1");
      return EXIT_FAILURE;
    }
    FILE *out_fptr2 = fopen(argv[3],"w+");
    if(out_fptr2 == NULL){
      fprintf(stderr,"failed to open file output2");
      return EXIT_FAILURE;
    }

    FILE *out_fptr3 = fopen(argv[4],"w+");
    if(out_fptr3 == NULL){
      fprintf(stderr,"failed to open file output2");
      return EXIT_FAILURE;
    }

    //CODE
    print_weight(fptr,weight); 
    priority_queue_by_weight(weight,out_fptr,out_fptr2,out_fptr3);

    fclose(out_fptr3);
    fclose(out_fptr2);
    fclose(out_fptr);
  }
  fclose(fptr);
  return EXIT_SUCCESS;
}
