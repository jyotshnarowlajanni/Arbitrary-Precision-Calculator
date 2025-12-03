/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stdlib.h>
#include <string.h>

int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR)
{
    /* If divisor = 0 → error */
    if (*head2 == NULL || ((*head2)->data == 0 && (*head2)->next == NULL))
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    /* If numerator = 0 → result = 0 */
    if (*head1 == NULL || ((*head1)->data == 0 && (*head1)->next == NULL))
    {
        dl_insert_last(headR, headR, 0);
        return SUCCESS;
    }

    /* If num1 < num2 → quotient = 0 */
    if (compare_lists(*head1, *head2) < 0)
    {
        dl_insert_last(headR, headR, 0);
        return SUCCESS;
    }

    /* Remainder list used during long division */
    Dlist *remH = NULL, *remT = NULL;

    /* Pointers for scanning dividend left to right */
    Dlist *scan = *head1;

    /* quotient head */
    *headR = NULL;

    /* Long division: take digits from left to right */
    while (scan != NULL)
    {
        /* Append current digit to remainder */
        dl_insert_last(&remH, &remT, scan->data);

        /* Remove leading zeros from remainder */
        while (remH && remH->data == 0 && remH->next != NULL)
        {
            Dlist *tmp = remH;
            remH = remH->next;
            remH->prev = NULL;
            free(tmp);
        }

        /* Count how many times divisor fits inside remainder */
        int count = 0;

        while (compare_lists(remH, *head2) >= 0)
        {
            Dlist *newRem = NULL;

            /* subtract divisor from remainder */
            subtraction(&remH, &remT, head2, tail2, &newRem);

            /* Update remainder */
            dl_delete_list(&remH, &remT);
            remH = newRem;

            /* Fix remainder tail */
            remT = remH;
            if (remT)
                while (remT->next)
                    remT = remT->next;

            count++;
        }

        /* Insert digit of quotient */
        dl_insert_last(headR, headR, count);

        scan = scan->next;
    }

    /* Remove leading zeros from quotient */
    while (*headR && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *del = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(del);
    }

    return SUCCESS;
}

