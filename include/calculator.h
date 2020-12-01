/*
 * Simple Calculator
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "stack.h"

typedef struct calculator calc_t;

typedef enum
{
	SUCCESS,
	MATH_ERROR,
	SYNTAX_ERROR
} status_t;

/*
 * Calculator Init: Initializing the new calculator
 * Return: calc_t - Pointer to the new calculator, if error will return NULL
 * Receive: size_t - The maximum length of the string deliverd
 * Time Complexity: O(1)
 */
calc_t *CalculatorInit(size_t max_length);

/*
 * Calculator Destroy: Frees all the memory being used by the calculator
 * Receive: calc_t - Pointer to the calculator
 * Time Complexity: O(1)
 */
void CalculatorDestroy(calc_t *calc);

/* CalculatorCalculate: Calculates the result of the string
 * Return: double - the result found. Will return 0 if there is an error with
 * 		   a remark of the error
 * Receive:
 * - const char * - Pointer to the string given
 * - status_t * - Pointer to the current status
 * - calc_t * - Pointer to the main calculator
 * Time Complexity: O(1)
 */
double CalculatorCalculate(const char *str, status_t *status, calc_t *calc);

#endif /* CALCULATOR_H */










