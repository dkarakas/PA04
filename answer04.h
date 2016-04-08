#ifndef PE10_H
#define PE10_H


 typedef struct _lnode {
   long int weight;
   char ch;
   struct _lnode* linked;
   struct _lnode* l_node;
   struct _lnode* r_node; 
 }lnode; 

 void print_weight(FILE*file,FILE*output,long int*weight);
 void priority_queue_by_weight(FILE*file, long int*weight,FILE*file2);

#endif
