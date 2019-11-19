/*********************************************************************************
* File name		: MagicSquare_using_CPointers.c
* Author		: Athul Sasi
* Description	: Magic square implementation using C pointers
* Remarks		: This' an implementation using pointers that I did in my free time.
*				  Rudimentary tests have been successfully performed. Test values
*				  are hard coded in the main() method at the end of this file.
*				  Note - Compiled using Microsoft Visual Studio Express 2017.
*********************************************************************************/

#include <stdio.h>		/* for printf */
#include <stdlib.h>		/* for malloc, free */

// Definitions for improving code readability
#define IN
#define OUT
#define INOUT

/*******************************************************************************
* Function name         : Allocate2DArray
* Author                : Athul Sasi
* Function description  : Allocates memory for the magic square represented as a 
*						  2D array
********************************************************************************/
void Allocate2DArray(IN int nArraySize, OUT int*** ppp2DArray)
{
	int i = 0;	/* Loop index */

	if (NULL == ppp2DArray)
	{
		return;
	}

	*ppp2DArray = (int**)malloc(nArraySize * sizeof(int*));
	if (NULL == *ppp2DArray)
	{
		return;
	}

	/* Note: Accessing an element syntax:
	  *(*(ary + i) + j); */

	for (i = 0; i < nArraySize; ++i) {
		*(*ppp2DArray + i) = (int*)malloc(nArraySize * sizeof(int));
		if (NULL == *(*ppp2DArray + i)) {
			printf("\nError msg\n");
		}
		else {
			/* Note: Elements could be initialized with memset. */
			int *p = NULL;
			p = *(*ppp2DArray + i);
			for (int j = 0; j < nArraySize; ++j) {
				*(p + j) = 0;
			} /* End of for (j) loop */
		}
	} /* End of for (i) loop */
}


/*******************************************************************************
* Function name         : Free2DArray
* Author                : Athul Sasi
* Function description  : Deallocate the memory of the 2D array
********************************************************************************/
void Free2DArray(IN int nArraySize, INOUT int*** ppp2DArray)
{
	int i = 0;	/* Loop index */

	if (NULL == ppp2DArray)
	{
		return;
	}


	/* Cleanup array */
	for (i = 0; i < nArraySize; ++i) {
		if (*(*ppp2DArray + i) != NULL)
		{
			free(*(*ppp2DArray + i));
			*(*ppp2DArray + i) = NULL;
		}
	}

	/* Cleanup pointer-to-pointer */
	if (*ppp2DArray != NULL)
	{
		free(*ppp2DArray);
		*ppp2DArray = NULL;
	}
}

/*******************************************************************************
* Function name         : InitFirstElement
* Author                : Athul Sasi
* Function description  : Initializes the first element in the 2D array
********************************************************************************/
void InitFirstElement(IN int **ary, IN int nArraySize, OUT int* pnXCoord, OUT int* pnYCoord)
{
	/* Bottom row middle co-ordinate */
	*pnXCoord = nArraySize - 1;
	*pnYCoord = nArraySize / 2;

	/* Initialize the first digit '1'. */
	*(*(ary + *pnXCoord) + *pnYCoord) = 1;
}

/*******************************************************************************
* Function name         : GetCoordinates
* Author                : Athul Sasi
* Function description  : Calculates the co-ordinates of the array where a value
*						  is to be set.
********************************************************************************/
void GetCoordinates(OUT int* pnXCoord, OUT int* pnYCoord, IN int **ary, IN int nArraySize, 
					INOUT int* pnLastXCoord, INOUT int* pnLastYCoord)
{
	*pnXCoord = *pnLastXCoord;
	*pnYCoord = *pnLastYCoord;

	/* Increment co-ordinates to next position */
	*pnXCoord = *pnXCoord + 1;
	*pnYCoord = *pnYCoord + 1;

	/* 1) Check if it has exceeded the boundary */
	if (*pnXCoord > (nArraySize - 1))
	{
		/* Reset to beginning of row */
		*pnXCoord = 0;
	}

	if (*pnYCoord > (nArraySize - 1))
	{
		/* Reset to beginning of column */
		*pnYCoord = 0;
	}

	/* 2) Check if it is already filled */
	if (0 != *(*(ary + *pnXCoord) + *pnYCoord))
	{
		/* Get previous position */
		*pnXCoord = *pnLastXCoord;
		*pnYCoord = *pnLastYCoord;

		*pnXCoord = *pnXCoord - 1;
		/* TODO: Verify if it has by chance exceeded boundary though it should never happen */
		if (*pnXCoord < 0)
		{
			*pnXCoord = nArraySize - 1;
		}
	}

	*pnLastXCoord = *pnXCoord;
	*pnLastYCoord = *pnYCoord;
}


/*******************************************************************************
* Function name         : FillMagicSquare
* Author                : Athul Sasi
* Function description  : Populate the magic square with integer values
********************************************************************************/
void FillMagicSquare(IN int nValue, INOUT int **ary, IN int nArraySize, INOUT int* pnLastXCoord, INOUT int* pnLastYCoord)
{
	int nXCoord = 0;
	int nYCoord = 0;

	/* Check if it is a valid position */
	GetCoordinates(&nXCoord, &nYCoord, ary, nArraySize, pnLastXCoord, pnLastYCoord);

	/* Initialize the value at the calculated co-ordinate. */
	*(*(ary + nXCoord) + nYCoord) = nValue;

	*pnLastXCoord = nXCoord;
	*pnLastYCoord = nYCoord;
}


/*******************************************************************************
* Function name         : CreateMagicSquare
* Author                : Athul Sasi
* Function description  : Creates the magic square and populates it with integers
********************************************************************************/
void CreateMagicSquare(IN int **ary, IN int nArraySize)
{
	int nXCoord		= 0;
	int nYCoord		= 0;

	int nXLastCoord = 0;
	int nYLastCoord = 0;

	int i			= 0; /* Loop index */

	/* Get back the co-ordinates */
	InitFirstElement(ary, nArraySize, &nXCoord, &nYCoord);

	nXLastCoord = nXCoord;
	nYLastCoord = nYCoord;

	for (i = 2; i <= (nArraySize * nArraySize); ++i) {
		/* Set values */
		FillMagicSquare(i, ary, nArraySize, &nXLastCoord, &nYLastCoord);
	}
}


/*******************************************************************************
* Function name         : DisplayMagicSquare
* Author                : Athul Sasi
* Function description  : Displays the magic square on the console
********************************************************************************/
void DisplayMagicSquare(IN int **ary, IN int nSize)
{
	int i = 0;	/* Loop index */
	int j = 0;	/* Loop index */

	for (i = 0; i < nSize; ++i) {
		printf("\n-------\n");
		printf("|");
		for (j = 0; j < nSize; ++j) {
			printf("%d", *(*(ary + i) + j));
			printf("|");
		}
	}
	printf("\n-------\n");
}


/*******************************************************************************
* Function name         : main
* Author                : Athul Sasi
* Function description  : Application's entry point. Also contains hard coded test 
*						  data to test different square sizes.
********************************************************************************/
void main()
{
	/*===========================================================
	  Test data : Please set same size for X & Y (it's a square!)
	 ============================================================ */

	int sizeY = 3;
	int sizeX = 3;
	/*int sizeY = 5;
	int sizeX = 5;
	int sizeY = 7;
	int sizeX = 7;*/

	
	int **ary = NULL; // Double pointer used to create the 2D array

	printf("Magic square of size %d \n\n", sizeX);


	Allocate2DArray(sizeY, &ary);	// Allocate the 2D array

	CreateMagicSquare(ary, sizeY);	// Create the magic square!

	DisplayMagicSquare(ary, sizeY); // Diplay the magic square on the console

	Free2DArray(sizeY, &ary);		// Free the 2D array


	printf("\n\nPlease press any key to exit..\n");
	getchar(); /* Wait for input from user to exit */
}
