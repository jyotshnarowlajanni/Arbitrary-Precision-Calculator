#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1

#include <stdio.h>

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

/* Include the prototypes here */ 
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR) ;
int create_list(Dlist **head, Dlist **tail, char *num);
int dl_insert_first(Dlist **head, int data);
int dl_insert_last(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
void dl_delete_list(Dlist **head, Dlist **tail);
int compare_lists(Dlist *h1, Dlist *h2);
#endif
