/*
 * Bit Array
 */

#include <stdio.h>	/* printf() */
#include <assert.h> /* assert() */

#ifndef BIT_ARRAY
#define BIT_ARRAY
#define CHAR_BITS 8 /* Size of a character */
#define ARR_SIZE (sizeof(size_t) * CHAR_BITS)	/* Amount of bits */

/* Turns on the requested index */
size_t BitArraySetOn(size_t arr, size_t index);

/* Turns off the requested index */
size_t BitArraySetOff(size_t arr, size_t index);

/* Turns on all the bits */
size_t BitArraySetAll();

/* Turns off all the bits */
size_t BitArrayResetAll(size_t arr);

/* Turns a certain index to a requested value (0 or 1) */
size_t BitArraySetBit(size_t arr, size_t index, int value);

/* Gets the value (0 or 1) of the requested index */
int BitArrayGetVal(size_t arr, size_t index);

/* Switches the state a certain index is */
size_t BitArrayFlipBit(size_t arr, size_t index);

/* Rotates all the indexes to the right "n" times */
size_t BitArrayRotR(size_t arr, int n);

/* Rotates all the indexes to the left "n" times */
size_t BitArrayRotL(size_t arr, int n);

/* Mirror all the indexes (right - left) */
size_t BitArrayMirror(size_t arr);

/* Mirror all the indexes - using LUT */
size_t BitArrayLUTMirror(size_t arr);

/* Counts the amount of indexes that are on */
size_t BitArrayCountOn(size_t arr);

/* Counts the amount of indexes that are on - using LUT */
size_t BitArrayLUTCountOn(size_t arr);

/* Counts the amount of indexes that are off */ /*can use total - Counton*/
size_t BitArrayCountOff(size_t arr);

/* Recieve bit array, returns (sizeof(bit_array) + 1)*64 */
char *BitArrayToString(size_t arr, char *buffer);

#endif /* BITARRAY_H */




