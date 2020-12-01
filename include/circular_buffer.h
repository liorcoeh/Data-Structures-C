/*
 * Circular Buffer
 */

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <unistd.h> /* size_t, ssize_t */

#include "utility.h"

typedef struct circular_buffer cb_t;

/*
 * CB Create: Creates a new circular buffer
 * Return: Pointer to the new circular buffer. In case
 * of failure will return NULL
 * Recieve: The capacity for the total buffer
 * Time Complexity: O(1)
 */
cb_t *CBCreate(size_t capacity);

/*
 * CB Destroy: Frees all the memory allocated for the circular buffer
 * Recieve: Pointer to the circular buffer
 * Time Complexity: O(1)
 */
void CBDestroy(cb_t *cb);

/*
 * CB Read: Puts the data in a buffer and removes it from the cirular buffer
 * Return: ssize_t 0 for seccess
 * Recieve:
 * - Pointer to the circular buffer
 * - Pointer to a buffer that the data will be put in it
 * - Size_t count for the amount of bytes you want to get out
 * Time Complexity: O(n)
 */
ssize_t CBRead(cb_t *cb, void *buf, size_t count);

/*
 * CB Write: Gets the data from a buffer and puts it in the cirular buffer
 * Return: ssize_t 0 for seccess or 1 for failure
 * Recieve:
 * - Pointer to the circular buffer
 * - Pointer to a buffer that holds the data to put in the circular buffer
 * - Size_t count for the amount of bytes you want to put in
 * Time Complexity: O(n)
 */
ssize_t CBWrite(cb_t *cb, const void *buf, size_t count);

/*
 * CB Free Space: Checks how much free space is left in the circular buffer
 * Return: The amount of free space in the cirular buffer
 * Recieve: Pointer to circular buffer
 * Time Complexity: O(1)
 */
size_t CBFreeSpace(cb_t *cb);

/*
 * CB Size: Gets the amount of occupied space in the circular buffer
 * Return: The amount of occupied space in the circular buffer
 * Recieve: Pointer to the circular buffer
 * Time Complexity: O(1)
 */
size_t CBSize(cb_t *cb);

/*
 * CB Is Empty: Checks if the circular buffer is empty or not
 * Return: 1 if the circular buffer is empty, or 0 if it's not
 * Recieve: Pointer to the circular buffer
 * Time Complexity: O(1)
 */
bool CBIsEmpty(cb_t *cb);

/*
 * CB Capacity: Gets the total capacity of circular buffer
 * Return: The capacity of the circular buffer
 * Recieve: Pointer to the circular buffer
 * Time Complexity: O(1)
 */
size_t CBCapacity(cb_t *cb);

#endif /* CIRCULAR_BUFFER_H */











