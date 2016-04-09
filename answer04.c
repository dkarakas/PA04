#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"answer04.h"

lnode * n_construct(int ch, long int weight);
lnode * Enqueue(lnode ** head,int ch, long int weight);
lnode * Enque_tree(lnode ** head, lnode *new_node);
lnode * Combine_two_nodes(lnode* new_one,lnode* new_two);
lnode * Dequeue(lnode ** head);
void destroy_list(lnode* head);
void print_tree(lnode *head, FILE* print,lnode **new);
void stack_pop(lnode **head);
void stack_push_end(lnode **head, int path);
void post_order_char_print(lnode *head,FILE*fptr);

void print_weight(FILE*fptr,long int*weight){
  //VARIABLES
  int int_ch;
  char ch;

  //FILE OPERATIONS
  fseek(fptr,0,SEEK_SET);
  while((ch=fgetc(fptr))!=EOF){
    int_ch = (int) ch; 
    weight[int_ch]++;
  }
}

void priority_queue_by_weight(long int*weight,FILE*fptr,FILE*fptr2){
  lnode *head = NULL;
  lnode *new_node =NULL;
  lnode *new = NULL;
  int total_weight = 0;
  int i;
  //print_list(head);
  for(i = 0; i < 256; i++){
    if(weight[i] != 0){
      new_node = Enqueue(&head,i,weight[i]); 
      total_weight += weight[i];
    }
  }
  if(head == NULL)
    return;
  lnode *node_one;
  lnode *node_two;
  lnode *node_comb;
  //CREATING TREE 
  while(head->weight != total_weight){
    node_one = Dequeue(&head);
    node_two = Dequeue(&head);
    node_comb = Combine_two_nodes(node_one,node_two);
    Enque_tree(&head,node_comb);
  }
  print_tree(head,fptr,&new);
  post_order_char_print(head,fptr2);
  fprintf(fptr2,"0");//adding the additional 0 requried that indicates the end of the topology
  destroy_list(head);
}

lnode* n_construct(int ch,long int weight){
  lnode* new_node = (lnode *)malloc(sizeof(lnode));
  if(new_node == NULL){
    fprintf(stderr,"failed to malloc new node");
    return NULL;
  }
  new_node->weight = weight;
  new_node->ch = (char)ch;
  new_node->l_node = NULL;
  new_node->r_node = NULL;
  new_node->linked = NULL;
  return new_node;
} 

lnode* Enqueue(lnode **head,int ch,long int weight){
  lnode* new_node = n_construct(ch,weight);
  if(new_node == NULL){
    fprintf(stderr,"failed to malloc new node");
    return NULL;
  }
  lnode dummy;
  lnode* prev = &dummy;
  lnode* cur = *head;
  dummy.linked= *head;
  while(cur != NULL){
    if(cur->weight > new_node->weight){
      break;}
    else if(cur->weight == new_node->weight){
        if((int) cur->ch > (int) new_node->ch ){
          fprintf(stderr,"\ncur(big) %c %ld prec(smal) %c %ld \n",cur->ch,cur->weight,new_node->ch,new_node->weight);
          break;
        }
        prev = cur;
        cur = cur->linked;
    }else{
          prev = cur;
          cur = cur->linked;
    }
  }
  prev->linked= new_node;
  new_node->linked = cur;
  *head = dummy.linked;
  return new_node;
}


void destroy_list(lnode *head){
  if(head==NULL)
    return;
  destroy_list(head->r_node);
  destroy_list(head->l_node);
  free(head);
}

lnode * Dequeue(lnode ** head){
  if(*head == NULL)
    return NULL;
  lnode* ret_node = NULL;
  ret_node = *head;
  *head = ret_node->linked;
  ret_node->linked = NULL;
    return ret_node;
}

lnode * Combine_two_nodes(lnode* new_one,lnode* new_two){
  lnode* new_node = (lnode*)malloc(sizeof(lnode));
  if(new_node == NULL)
    return NULL;
  new_node->l_node = new_one;
  new_node->r_node = new_two;
  new_node->weight = new_one->weight+new_two->weight;
  return new_node;  
}

lnode * Enque_tree(lnode ** head, lnode *new_node){
  if(*head == NULL){
    return *head = new_node;
  }
  lnode dummy;
  dummy.linked = *head;
  lnode* prev = &dummy;
  lnode* cur = *head;

  while(cur!=NULL){
    if(cur->weight > new_node->weight){
       break;
    }
    prev = cur;
    cur = cur->linked;
  }
  *head =dummy.linked;
  prev->linked = new_node;
  new_node->linked = cur;
  return new_node;
}

void print_tree(lnode *head, FILE* print,lnode **new){
  if(head->l_node == NULL && head->r_node == NULL){
    fprintf(print,"%c:",head->ch);
    lnode *temp = *new;
    while(temp != NULL){
      fprintf(print,"%ld",temp->weight);
      temp = temp->linked;
    }
    fprintf(print,"\n");
    return;
  }
  stack_push_end(new,0);
  print_tree(head->l_node,print,new);
  stack_pop(new);
  stack_push_end(new,1);
  print_tree(head->r_node,print,new);
  stack_pop(new);

}

void post_order_char_print(lnode *head,FILE* fptr){
  if(head->l_node == NULL && head->r_node == NULL){
    fprintf(fptr,"1");
    fprintf(fptr,"%c",(char)head->ch);
    return;
  }else if(head->l_node == NULL || head->r_node == NULL){
    fprintf(stderr,"unexpected node reached");
    return;
  }
  post_order_char_print(head->l_node,fptr);
  post_order_char_print(head->r_node,fptr);
  fprintf(fptr,"0");
}

void stack_push_end(lnode **head, int path){
  lnode *temp = *head;
  lnode* new_car = n_construct(2,(long int)path);
  if(new_car == NULL){
    return;
  }
  if(temp == NULL){
    *head = new_car;
    return;
  }
  while(temp->linked != NULL)
    temp = temp->linked;
  new_car->linked = NULL;
  temp ->linked = new_car;
}

void stack_pop(lnode **list){
  if(*list == NULL)
    return;
  lnode *cur = *list;
  lnode *prev = cur;
  if(cur->linked == NULL){ *list = NULL; free(cur);return; }else{
  while(cur->linked != NULL){
    prev = cur;
    cur = cur->linked; 
  }
  prev->linked = NULL;
  free(cur);
  return ;}
  
}

