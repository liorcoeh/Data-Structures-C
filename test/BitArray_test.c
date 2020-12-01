/*
 * Bit Array - Test File
 */

#include "BitArray.h"

int main()
{
	size_t arr = 101010101010101;
	size_t i = 0;
	char buffer[ARR_SIZE];
		
/*****************************************************************************/	

	/* Checking BitArrayCountOn() and BitArrayCountOff() functions */
	if((30 == BitArrayCountOn(arr)) && (34 == BitArrayCountOff(arr)))
	{
		printf("\nCountOn() and CountOff() functions seems fine\n\n");
	}
	else
	{
		printf("There is a problem with CountOn and/or CountOff() functions\n");
	}
	
/*****************************************************************************/	

	/* Checking BitArrayLUTCountOn() function */
	if(30 == BitArrayLUTCountOn(arr))
	{
		printf("BitArrayLUTCountOn() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayLUTCountOn function\n");
	}
	
/*****************************************************************************/		
	
	/* Checking the BitArrayResetAll() function */
	arr = BitArrayResetAll(arr);
	if(0 == BitArrayCountOn(arr))
	{
		printf("BitArrayResetAll() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayResetAll() function\n");
	}
	
/*****************************************************************************/

	/* Checking the BitArrayToString() function - it should show all "0" */
	
	printf("%s\n\n",BitArrayToString(arr, buffer));
	
/*****************************************************************************/

	/* Checking the BitArraySetAll() function */
	
	arr = BitArraySetAll();
	if(64 == BitArrayCountOn(arr))
	{
		printf("BitArraySetAll() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArraySetAll() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArraySetOff() function */
		
	for(i = 0; i < ARR_SIZE; i += 2)
	{
		arr = BitArraySetOff(arr, i);
	}
	
	if(32 == BitArrayCountOn(arr))
	{
		printf("BitArraySetOff() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArraySetOff() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArraySetOn() function */
	
	for(i = 0; i < ARR_SIZE; i += 3)
	{
		arr = BitArraySetOn(arr, i);
	}
	
	if(43 == BitArrayCountOn(arr))
	{
		printf("BitArraySetOn() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArraySetOn() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArrayGetVal() function */
	
	if((0 == BitArrayGetVal(arr, 2)) && (1 == BitArrayGetVal(arr, 63)))
	{
		printf("BitArrayGetVal() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayGetVal() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArraySetBit() function */
	
	arr = BitArraySetBit(arr, 2, 1);
	arr = BitArraySetBit(arr, 63, 0);
	
	if((1 == BitArrayGetVal(arr, 2)) && (0 == BitArrayGetVal(arr, 63)))
	{
		printf("BitArraySetBit() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArraySetBit() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArrayFlipBit() function */
	
	arr = BitArrayFlipBit(arr, 2);
	arr = BitArrayFlipBit(arr, 63);
	
	if((0 == BitArrayGetVal(arr, 2)) && (1 == BitArrayGetVal(arr, 63)))
	{
		printf("BitArrayFlipBit() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayFlipBit() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArrayMirror() function */
	
	arr = 512;
	arr = BitArrayMirror(arr);
	
	if((0 == BitArrayGetVal(arr, 9)) && (1 == BitArrayGetVal(arr, 54)))
	{
		printf("BitArrayMirror() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayMirror() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArrayLUTMirror() function */
	
	arr = 512;
	arr = BitArrayLUTMirror(arr);
	
	if((0 == BitArrayGetVal(arr, 9)) && (1 == BitArrayGetVal(arr, 54)))
	{
		printf("BitArrayLUTMirror() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayLUTMirror() function\n");
	}
	
/*****************************************************************************/
	
	/* Checking the BitArrayRotR() function */
	
	arr = BitArrayRotR(arr, 10);
	
	if((1 == BitArrayGetVal(arr, 0)))
	{
		printf("BitArrayRotR() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayRotR() function\n");
	}
	
	
	
	
/*****************************************************************************/
	
	/* Checking the BitArrayRotL() function */
	
	arr = BitArrayRotL(arr, 33);
	
	if((1 == BitArrayGetVal(arr, 31)))
	{
		printf("BitArrayRotL() function seems fine\n\n");
	}
	else
	{
		printf("There is a problem with BitArrayRotL() function\n");
	}
	
/*****************************************************************************/		

	return (0);
}
