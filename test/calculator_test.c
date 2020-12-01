/*
 * Simple Calculator - Test File
 */

#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <time.h>					 /* time_t						  */

#include "calculator.h"					 /* all functions declerations	  */

static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestCalc(void);

int main(void)
{
	int err_sum = 0;

	err_sum += TestCalc();
	
	if (0 == err_sum)
	{
		puts("Calculator TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

static int TestCalc(void)
{
	int count_errs = 0;
	calc_t *calc = CalculatorInit(100);
	status_t i = SUCCESS;
	double result = 0;
	char str[100] = "7+8"/**2^(9-1*2^2-3)"*/; /* Result = 39 status = SUCCESS 	  */
	char str2[100] = "8+8*3+-2^5";		 /* Result =  0 status = SYNTAX_ERROR	  */
	char str3[100] = "8+8*3-2^";		 /* Result =  0 status = SYNTAX_ERROR */
	char str4[100] = "2/0";				 /* Result =  0 status = MATH_ERROR   */
	char str5[100] = "8+8*((3-2)*5)";	 /* Result = 48 status = SUCCESS 	  */
	char str6[100] = "3-2)*5";			 /* Result =  0 status = SYNTAX_ERROR */


	printf("\nTest number 1: result should be (39) and status should be (0):\n");
	result =  CalculatorCalculate(str, &i, calc);
	printf("The result is: %f\n", result);
	printf("The status is: %d\n\n", i); 
	count_errs += Tester(result, 15, "Test 1 result: ", __LINE__);
	count_errs += Tester(i, SUCCESS, "Test 1 status: ", __LINE__);


	printf("\nTest number 2: result should be (0) and status should be (2):\n");
	result =  CalculatorCalculate(str2, &i, calc);
	printf("The result is: %f\n", result);
	printf("The status is: %d\n\n", i);
	count_errs += Tester(result, 0, "Test 2 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 2 status: ", __LINE__);

	
	printf("\nTest number 3: result should be (0) and status should be (2):\n");
	result =  CalculatorCalculate(str3, &i, calc);
	printf("The result is: %f\n", result);
	printf("The status is: %d\n\n", i);
	count_errs += Tester(result, 0, "Test 3 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 3 status: ", __LINE__);

	
	printf("\nTest number 4: result should be (0) and status should be (1):\n");
	result =  CalculatorCalculate(str4, &i, calc);
	printf("The result is: %f\n", result);
	printf("The status is: %d\n\n", i);
	count_errs += Tester(result, 0, "Test 4 result: ", __LINE__);
	count_errs += Tester(i, MATH_ERROR, "Test 4 status: ", __LINE__);


	printf("\nTest number 5: result should be (48) and status should be (0):\n");
	result =  CalculatorCalculate(str5, &i, calc);
	printf("The result is: %f\n", result);
	printf("The status is: %d\n\n", i);
	count_errs += Tester(result, 48, "Test 5 result: ", __LINE__);
	count_errs += Tester(i, SUCCESS, "Test 5 status: ", __LINE__);

	
	printf("\nTest number 6: result should be (0) and status should be (2):\n");
	result =  CalculatorCalculate(str6, &i, calc);
	printf("The result is: %f\n", result);
	printf("The status is: %d\n\n", i);
	count_errs += Tester(result, 0, "Test 6 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 6 status: ", __LINE__);
	
	
	CalculatorDestroy(calc);

	return(count_errs);
}


static int Tester(long actual_value, long expected_value, char *str, int line)
{	
	if (actual_value != expected_value)
	{
		printf("function: %s  in line: %d ", str, line);
		printf("- status: fail... expected value was %ld and actual\
		 value is %ld\n",
				expected_value, actual_value);
		puts("");
				
		return (1);
	}
	
	return (0);
}
