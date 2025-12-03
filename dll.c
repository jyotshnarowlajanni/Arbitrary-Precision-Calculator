#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

//int create_list
int create_list(Dlist **head, Dlist **tail, char *num)
{
    int i = 0;

    // Check for NULL input
    if(num == NULL)
        return FAILURE;

    // Traverse each character in the string
    while(num[i] != '\0')
    {
        // Convert char digit to int digit
        int digit = num[i] - '0';

        // Validation: Check if character is a valid digit
        if(digit < 0 || digit > 9)
        {
            printf("Invalid number: Only digits allowed\n");
            return FAILURE;
        }

        // Insert digit into DLL (insert at last)
        Dlist *new = malloc(sizeof(Dlist));
        if(new == NULL)
        {
            printf("Memory allocation failed\n");
            return FAILURE;
        }

        new->data = digit;
        new->prev = NULL;
        new->next = NULL;

        // First node
        if(*head == NULL)
        {
            *head = new;
            *tail = new;
        }
        else
        {
            // Attach at last
            (*tail)->next = new;
            new->prev = *tail;
            *tail = new;
        }

        i++;
    }

    return SUCCESS;
}

int list_to_int(Dlist *head)
{
    int result = 0;
    Dlist *temp = head;
    while (temp)
    {
        result = result * 10 + temp->data;
        temp = temp->next;
    }
    return result;
}
int dl_insert_first(Dlist **head, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head != NULL)
        (*head)->prev = new;

    *head = new;
    return SUCCESS;
}


int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    if (*tail != NULL)
        (*tail)->next = new;
    else
        *head = new;

    *tail = new;
    return SUCCESS;
}

void print_list(Dlist *head)
{
    Dlist *temp = head;
    while (temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void dl_delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;
    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *tail = NULL;
}
