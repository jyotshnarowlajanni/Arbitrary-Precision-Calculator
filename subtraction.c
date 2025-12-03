/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stdlib.h> // For free()

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR)
{
    int isNegative = 0;

    // 1. Compare the lists (by calling the helper function)
    int cmp = compare_lists(*head1, *head2);

    // If numbers are equal, result is 0
    if (cmp == 0)
    {
        // Ensure result list is 0, not empty
        if (*headR == NULL) {
            // Assuming dl_insert_first also sets the tail pointer, 
            // but since we only use headR, we'll just insert.
            // You might need to update *tailR here if it's used elsewhere.
            dl_insert_first(headR, 0); 
        } else {
             // Clear list and insert 0 if not already handled
        }
        return 0;
    }

    
    // 2. Swap if num2 is larger (to ensure num1 - num2 is |Larger| - |Smaller|)
    if (cmp < 0)
    {
        isNegative = 1; // Set flag to indicate the result is negative

        // Swap head and tail pointers
        Dlist *h = *head1, *t = *tail1;
        *head1 = *head2;  *tail1 = *tail2;
        *head2 = h;       *tail2 = t;
    }

    // Pointers for subtraction, starting from tails (LSD)
    Dlist *p1 = *tail1;
    Dlist *p2 = *tail2;
    int borrow = 0;
    
    // 3. Perform subtraction: (Larger - Smaller)
    while (p1 != NULL) // We only need to check p1 since it holds the larger number
    {
        int d1 = p1->data;
        int d2 = 0;

        if (p2)
        {
            d2 = p2->data;
            p2 = p2->prev;
        }

        int diff = d1 - d2 - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        dl_insert_first(headR, diff);
        p1 = p1->prev;
    }

    // 4. Remove leading zeros (except for the last digit if it's 0)
    while (*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *tmp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        // Assuming there is a function to free the node, e.g., free(tmp)
        free(tmp); 
    }

    return isNegative; // Return sign flag to main
}
int compare_lists(Dlist *h1, Dlist *h2)
{
    // Traverse lists to find lengths
    int len1 = 0, len2 = 0;
    Dlist *t1 = h1, *t2 = h2;

    while (t1) { len1++; t1 = t1->next; }
    while (t2) { len2++; t2 = t2->next; }

    // Compare lengths first
    if (len1 > len2) 
        return 1;
    if (len1 < len2) 
        return -1;

    // Lengths are equal, compare digit by digit from MSD (head)
    t1 = h1;
    t2 = h2;

    while (t1 && t2)
    {
        if (t1->data > t2->data) 
            return 1;
        if (t1->data < t2->data) 
            return -1;
        t1 = t1->next;
        t2 = t2->next;
    }

    return 0; // Equal
}