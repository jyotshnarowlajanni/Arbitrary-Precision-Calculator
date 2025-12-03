
/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
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

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	/* Definition goes here */
	if (*head1 == NULL && *head2 == NULL)
	{
		return FAILURE;
	}

	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	data_t carry = 0, sum ;
	/* Add digits from the tail (least significant digit) towards the head */
	while (temp1 != NULL || temp2 != NULL)
	{
		if(temp1 != NULL && temp2 != NULL)
		{
			sum = carry + temp1->data + temp2->data;
			if(sum > 9)
			{
				carry = 1;
				sum = sum % 10;
			}
			else
			{
				carry = 0;
			}

			dl_insert_first(headR, sum) ;
			temp1 = temp1->prev;
			temp2 = temp2->prev;
			
		}
		else if(temp1 != NULL && temp2 == NULL)
		{
			sum = carry + temp1->data;
			if(sum > 9)
			{
				carry = 1;
				sum = sum % 10;
			}
			else
			{
				carry = 0;
			}

			dl_insert_first(headR, sum) ;
			temp1 = temp1->prev;
		}
		else if(temp1 == NULL && temp2 != NULL)
		{
			sum = carry + temp2->data;
			if(sum > 9)
			{
				carry = 1;
				sum = sum % 10;
			}
			else
			{
				carry = 0;
			}

			dl_insert_first(headR, sum) ;
			temp2 = temp2->prev;
		}
	
		
	}

	/* If there's a remaining carry, insert it at the front */
	if (carry == 1)
	{
		dl_insert_first(headR, carry);
	}
	return SUCCESS; // Return appropriate status
}
