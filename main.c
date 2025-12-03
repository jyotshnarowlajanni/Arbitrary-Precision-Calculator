/**************************************************************************************************************************************************************
 *Title		: main function(Driver function)
 *Description	: This function is used as the driver function for the all the functions
 Name : Jyotshna Rowlajanni
 Date : 03-12-2025
 ***************************************************************************************************************************************************************/
#include "apc.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	/* Declare the pointers */
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;
	head1 = NULL;
	head2 = NULL;
	headR = NULL;
	tail1 = NULL;
	tail2 = NULL;
	tailR = NULL;

	char option;

	int sign1 = 1, sign2 = 1;  // +1 for positive, -1 for negative
	if(argc != 4)
	{
		printf("Invalid Input:-( Try again...\n");
		return FAILURE;
	}
	if (argv[1][0] == '-') 
	{
		sign1 = -1;
	}
	if (argv[3][0] == '-') 
	{
		sign2 = -1;
	}
	
	
	/* Code for reading the inputs */
	if(argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != '*' && argv[2][0] != '/')
    {
        printf("Invalid operator! Use only + - * /\n");
        return FAILURE;
    }
	/* Function for extracting the operator */
	
	/* For num1 */
	char *num1_str;
	if (argv[1][0] == '-' || argv[1][0] == '+')
	{
		num1_str = argv[1] + 1;   // Skip the sign
	}
	else
	{
		num1_str = argv[1];       // Use as is
	}

	if (create_list(&head1, &tail1, num1_str) == FAILURE)
	{
		printf("Failed to create list for num1\n");
		return FAILURE;
	}

	/* For num2 */
	char *num2_str;
	if (argv[3][0] == '-' || argv[3][0] == '+')
	{
		num2_str = argv[3] + 1;   // Skip the sign
	}
	else
	{
		num2_str = argv[3];       // Use as is
	}

	if (create_list(&head2, &tail2, num2_str) == FAILURE)
	{
		printf("Failed to create list for num2\n");
		return FAILURE;
	}

	    switch (argv[2][0])
    {
    case '+':
        /* call the function to perform the addition operation */
        /* Perform Addition or Subtraction */
        if (sign1 == sign2) 
        {
            addition(&head1, &tail1, &head2, &tail2, &headR);

            int isZero = (headR && headR->data == 0 && headR->next == NULL);

            printf("Result : ");
            if (sign1 == -1 && !isZero) 
                printf("-");

            print_list(headR);
            printf("\n");
        } 
        else 
        {
            int isNegative = subtraction(&head1, &tail1, &head2, &tail2, &headR);

            int isZero = (headR && headR->data == 0 && headR->next == NULL);

            printf("Result : ");

            /* Print sign only if result NON-ZERO */
            if (!isZero) 
            {
                if ((sign1 == -1 && !isNegative) || (sign2 == -1 && isNegative)) 
                    printf("-");
            }

            print_list(headR);
            printf("\n");
        }
        break;

    case '-':
        /* call the function to perform the subtraction operation */
        if (sign1 != sign2) 
        {
            /* Different signs → Addition */
            addition(&head1, &tail1, &head2, &tail2, &headR);
            printf("Result : ");
            if (sign1 == -1) printf("-");
            print_list(headR);
            printf("\n");
        } 
        else 
        {
            /* Same sign → Subtraction */
            int isNegative = subtraction(&head1, &tail1, &head2, &tail2, &headR);
            printf("Result : ");
            if (sign1 == 1) { /* +A - (+B) */
                if (isNegative) printf("-");
            } else { /* -A - (-B) = -A + B */
                if (!isNegative) printf("-");
            }
            print_list(headR);
            printf("\n");
        }
        break; /* <-- IMPORTANT: prevent fall-through */

    case '*':
        /* call the function to perform the multiplication operation */
        multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
        printf("Result : ");

        /* Print negative sign only if input signs differ AND result != 0 */
        if (sign1 != sign2) 
        {
            /* check if result is zero (single node with 0) */
            if (!(headR && headR->data == 0 && headR->next == NULL))
                printf("-");
        }

        print_list(headR);
        printf("\n");
        break;

    case '/':
        /* call the function to perform the division operation */
        int resultSign = 1;
        if (sign1 != sign2)
            resultSign = -1;

        /* Perform division */
        if (division(&head1, &tail1, &head2, &tail2, &headR) == FAILURE)
        {
            printf("Error: Division failed (possibly division by zero)\n");
            return FAILURE;
        }
         /* Remove sign for zero results */
        int isZero = (headR && headR->data == 0 && headR->next == NULL);

        printf("Result : ");
        if (resultSign == -1 && !isZero)
            printf("-");

        print_list(headR);
        printf("\n");
        break;
        
    default:
        printf("Invalid Input:-( Try again...\n");
    }


	/* Free the allocated memory */
	dl_delete_list(&head1, &tail1);
	dl_delete_list(&head2, &tail2);
	dl_delete_list(&headR, &tailR);


    return SUCCESS;
}
