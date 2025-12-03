/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
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

int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR, Dlist **tailR)
{
    /* Return failure if any input list is empty */
    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    Dlist *temp1 = NULL;
    Dlist *temp2 = *tail2;   /* Start multiplication from least significant digit of number2 */

    int carry = 0, product = 0;

    /* Temporary result lists */
    Dlist *hR1 = NULL, *tR1 = NULL;   /* One row of multiplication */
    Dlist *hR2 = NULL, *tR2 = NULL;   /* Accumulated result */
    Dlist *hR3 = NULL, *tR3 = NULL;   /* Addition output */

    int zero_count = 0;   /* Shifting position (like place value) */

    /* Outer loop: traverse number2 from last digit to first */
    while (temp2 != NULL)
    {
        /* Reset row list for each new multiplication row */
        hR1 = tR1 = NULL;

        /* Reset pointer to last digit of number1 */
        temp1 = *tail1;
        carry = 0;

        /* Inner loop: multiply number1 by one digit of number2 */
        while (temp1 != NULL)
        {
            /* Multiply digits + carry */
            product = temp1->data * temp2->data + carry;

            int rem = product % 10;   /* Extract single digit */
            carry = product / 10;     /* Update carry */

            /* Insert result digit at beginning (since digits come from LSB side) */
            dl_insert_first(&hR1, rem);
            if (tR1 == NULL)
                tR1 = hR1;

            temp1 = temp1->prev;
        }

        /* Insert final carry if non-zero */
        if (carry > 0)
        {
            dl_insert_first(&hR1, carry);
        }

        /* Correct tR1 to final node (tail) */
        tR1 = hR1;
        while (tR1 && tR1->next)
            tR1 = tR1->next;

        /* Add required number of zeros to represent place value (shifting left) */
        for (int i = 0; i < zero_count; i++)
        {
            dl_insert_last(&hR1, &tR1, 0);
        }

        /* FIRST ROW → directly copy into R2 */
        if (hR2 == NULL)
        {
            Dlist *p = hR1;
            while (p)
            {
                dl_insert_last(&hR2, &tR2, p->data);
                p = p->next;
            }
        }
        else
        {
            /* ADDITION: Add existing R2 and current R1 */
            hR3 = tR3 = NULL;

            /* addition() produces headR only; tail computed manually */
            addition(&hR1, &tR1, &hR2, &tR2, &hR3);

            /* Find tail of R3 */
            tR3 = hR3;
            if (tR3)
                while (tR3->next)
                    tR3 = tR3->next;

            /* Free old lists R1 and R2 */
            dl_delete_list(&hR1, &tR1);
            dl_delete_list(&hR2, &tR2);

            /* Store new sum into R2 */
            hR2 = hR3;
            tR2 = tR3;

            /* Reset R3 for next iteration */
            hR3 = tR3 = NULL;
        }

        /* Delete R1 after using it */
        dl_delete_list(&hR1, &tR1);

        /* Move to previous digit in number2 */
        temp2 = temp2->prev;

        /* Increase zero count (next place value) */
        zero_count++;
    }

    /* Remove leading zeros except single zero */
    while (hR2 && hR2->data == 0 && hR2->next != NULL)
    {
        Dlist *del = hR2;
        hR2 = hR2->next;
        hR2->prev = NULL;
        free(del);
    }

    /* Output */
    *headR = hR2;
    *tailR = tR2;

    return SUCCESS;
}
