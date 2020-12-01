/*
 * Simple Calculator - Functions Definitions
 */

#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <math.h>	/* pow()	*/

#include "calculator.h"
#include "stack.h"

#define ASCII_RANGE (256)
#define UNUSED(x) ((void)(x))

/*****************************************************************************/

typedef enum
{
	WAIT_FOR_NUM = 0,
	WAIT_FOR_OP = 1,
	ERROR = 2,
	STATE_RANGE
} state_t;

typedef enum
{
	NOTHING = 0,
	CLOSE_PAR,
	SUB,
	ADD = SUB,
	MULT,
	DIV = MULT,
	POW,
	OPEN_PAR
} operation_priority_t;

typedef struct
{
	void (*handler)(const char **char_ptr, status_t *status, calc_t *calc);
	state_t next_state;
} state_entry_t;

typedef struct
{
	status_t (*calc_func)(double *num1, double num2);
	operation_priority_t priority;
} operator_t;

struct calculator
{
	state_entry_t table[STATE_RANGE][ASCII_RANGE];
	operator_t operators[ASCII_RANGE];
	stack_t *num_stack;
	stack_t *op_stack;
}; /* calc_t */

/******************************************************************************/

/* The main function that checks the state of the calculator and assigns */
/* the right functions to do the right operations 						 */
static void MainHandler(const char *str, status_t *status, calc_t *calc);

/* Creates a lookup table for the calculator */
static void CreateStateTable(state_entry_t table[][ASCII_RANGE]);

/* Creates array for the math functions */
static void LUTOperations(operator_t operators[ASCII_RANGE]);

/* A function to deal with inapropriate inputs */
static void DigitErrorHandler(const char **str,
							  status_t *status, calc_t *calc);

/* A funtion that handels digits */
static void DigitHandler(const char **str, status_t *status, calc_t *calc);

/* A function that handels operands */
static void OperandHandler(const char **str,
							status_t *status, calc_t *calc);

/* A function that handels the '(' operand */
static void OpenBracketHandler(const char **str,
								   status_t *status, calc_t *calc);

/* A function that handels the ')' operand */
static void CloseBracketHandler(const char **str,
									status_t *status, calc_t *calc);

/* A function that handels the '\0' operand - end of string */
static void EndOfStrHandler(const char **str, status_t *status, calc_t *calc);

/* A function that gets the last number in the num_stack - the result */
static double GetFinalResult(calc_t *calc);

/* A function that empties both stack - after errors usually */
static void EmptyStacks(stack_t *stack1, stack_t *stack2);

/*****************************************************************************/

/* A function to deal with inapropriate inputs */
static status_t GeneralErrorHandler();

/* Funtion to add one num to another, the first one changes to the result */
static status_t Add(double *num1, double num2);

/* Funtion to subtructs one num from the other, the */
/* first one changes to the result					*/
static status_t Sub(double *num1, double num2);

/* Funtion to multiply one num by another, the first	*/
/* one changes to the result							*/
static status_t Mult(double *num1, double num2);

/* Funtion to divide one num by another, the first one changes to the result */
static status_t Div(double *num1, double num2);

/* Function to power one num by another, the first one changes to the result */
static status_t Pow(double *num1, double num2);

/*****************************************************************************/
/*****************************************************************************
								MAIN FUNCTIONS
							*********************/

calc_t *CalculatorInit(size_t max_length)
{
	calc_t *new_calc = NULL;
	stack_t *num_stack = NULL;
	stack_t *op_stack = NULL;
	
	new_calc = (calc_t *)malloc(sizeof(calc_t));
	
	if (NULL == new_calc)
	{
		return (NULL);
	}
	
	num_stack = StackCreate(max_length / 2 + 1);
	
	if (NULL == num_stack)
	{
		free(new_calc);
		new_calc = NULL;
		
		return (NULL);
	}
	
	op_stack = StackCreate(max_length / 2 + 1);
	
	if (NULL == num_stack)
	{
		free(new_calc);
		new_calc = NULL;
		free(num_stack);
		num_stack = NULL;
		
		return (NULL);
	}
	
	CreateStateTable(new_calc->table);
	LUTOperations(new_calc->operators);
	new_calc->num_stack = num_stack;
	new_calc->op_stack = op_stack;
	
	return (new_calc);
}

/*****************************************************************************/

void CalculatorDestroy(calc_t *calc)
{
	assert(calc);

	StackDestroy(calc->num_stack);
	StackDestroy(calc->op_stack);
	
	free(calc);
	calc = NULL;
}

/*****************************************************************************/

double CalculatorCalculate(const char *str, status_t *status, calc_t *calc)
{
	assert(str);
	assert(status);
	assert(calc);

	MainHandler(str, status, calc);

	if (SUCCESS != *status)
	{
		printf("%s\n", *status == 1 ? "MATH_ERROR" : "SYNTAX_ERROR");
		EmptyStacks(calc->num_stack, calc->op_stack);
		return (0);
	}
	
	return (GetFinalResult(calc));
}

/******************************************************************************/
/*****************************************************************************
								UTILITY FUNCTIONS
							************************/
static void MainHandler(const char *str, status_t *status, calc_t *calc)
{
	state_t current_state = WAIT_FOR_NUM;
	unsigned char operand = 0;

	assert(str);
	assert(status);
	assert(calc);
	
	while (*str)
	{
		operand = *str;
		calc->table[current_state][operand].handler(&str, status, calc);
		
		if (SUCCESS != *status)
		{
			return;
		}
		
		current_state = calc->table[current_state][operand].next_state;
		++str;
	}
	
	if (WAIT_FOR_NUM == current_state)
	{
		*status = SYNTAX_ERROR;
		return;
	}
	
	EndOfStrHandler(&str, status, calc);
}

static double GetFinalResult(calc_t *calc)
{
	double result = *((double *)StackPeek(calc->num_stack));

	assert(calc);

	free(StackPeek(calc->num_stack));
	StackPop(calc->num_stack);
	
	return (result);
}

/*****************************************************************************
								LOOK UP TABLES
							**********************/

static void LUTOperations(operator_t operators[ASCII_RANGE])
{
	int i = 0;
	
	for (i = 0; i < ASCII_RANGE; ++i)
	{
		operators[i].calc_func = GeneralErrorHandler;
		operators[i].priority = NOTHING;
	}
		
	operators['+'].calc_func = Add;
	operators['+'].priority = ADD;
	
	operators['-'].calc_func = Sub;
	operators['-'].priority = SUB;

	operators['*'].calc_func = Mult;
	operators['*'].priority = MULT;

	operators['/'].calc_func = Div;
	operators['/'].priority = DIV;

	operators['^'].calc_func = Pow;
	operators['^'].priority = POW;
}

static void CreateStateTable(state_entry_t table[][ASCII_RANGE])
{	
	int i = 0;
	int j = 0;
	
	/* Initializing all the elements in the LUT */
	for (i = 0; i < STATE_RANGE; ++i)
	{
		for (j = 0; j < ASCII_RANGE; ++j)
		{
			table[i][j].handler = DigitErrorHandler;
			table[i][j].next_state = ERROR;
		}
	}
	
	/* Handeling the brackets */
	
	table[0]['('].handler = OpenBracketHandler;
	table[0]['('].next_state = WAIT_FOR_NUM;
	
	table[1][')'].handler = CloseBracketHandler;
	table[1][')'].next_state = WAIT_FOR_OP;
	
	/* Handeling all the operators */	
	table[1]['+'].handler = OperandHandler;
	table[1]['+'].next_state = WAIT_FOR_NUM;
	
	table[1]['-'].handler = OperandHandler;
	table[1]['-'].next_state = WAIT_FOR_NUM;
	
	table[1]['*'].handler = OperandHandler;
	table[1]['*'].next_state = WAIT_FOR_NUM; 
	
	table[1]['/'].handler = OperandHandler;
	table[1]['/'].next_state = WAIT_FOR_NUM;
	
	table[1]['^'].handler = OperandHandler;
	table[1]['^'].next_state = WAIT_FOR_NUM;
	
	/* Handeling all the numbers */	
	table[0]['0'].handler = DigitHandler;
	table[0]['0'].next_state = WAIT_FOR_OP;
	
	table[0]['1'].handler = DigitHandler;
	table[0]['1'].next_state = WAIT_FOR_OP;
	
	table[0]['2'].handler = DigitHandler;
	table[0]['2'].next_state = WAIT_FOR_OP;
	
	table[0]['3'].handler = DigitHandler;
	table[0]['3'].next_state = WAIT_FOR_OP;
	
	table[0]['4'].handler = DigitHandler;
	table[0]['4'].next_state = WAIT_FOR_OP;
	
	table[0]['5'].handler = DigitHandler;
	table[0]['5'].next_state = WAIT_FOR_OP;
	
	table[0]['6'].handler = DigitHandler;
	table[0]['6'].next_state = WAIT_FOR_OP;
	
	table[0]['7'].handler = DigitHandler;
	table[0]['7'].next_state = WAIT_FOR_OP;
	
	table[0]['8'].handler = DigitHandler;
	table[0]['8'].next_state = WAIT_FOR_OP;
	
	table[0]['9'].handler = DigitHandler;
	table[0]['9'].next_state = WAIT_FOR_OP;
	
	table[0]['\0'].handler = EndOfStrHandler;
	table[0]['\0'].next_state = WAIT_FOR_NUM;

}

/*****************************************************************************
								   Handlers
							**********************/

static void DigitErrorHandler(const char **c, status_t *status, calc_t *calc)
{
	assert(c);
	assert(status);
	assert(calc);

	UNUSED(c);
	UNUSED(calc);
	*status = SYNTAX_ERROR;
}

static status_t GeneralErrorHandler()
{
	return (SYNTAX_ERROR);
}

static void DigitHandler(const char **str, status_t *status, calc_t *calc)
{
	double *digit = (double *)malloc(sizeof(double));

	assert(str);
	assert(status);
	assert(calc);
	
	*digit = strtod(*str, NULL);
	
	StackPush(calc->num_stack, digit);
	
	*status = SUCCESS;
}

static void OperandHandler(const char **str, status_t *status, calc_t *calc)
{
	double num2 = 0;
	unsigned char operand = 0;
	unsigned char new_str = **str;

	assert(str);
	assert(status);
	assert(calc);
	
	*status = SUCCESS;
	
	/* In case of the first operand was inserted */
	if (StackIsEmpty(calc->op_stack))
	{
		StackPush(calc->op_stack, (char *)*str);
		
		return;
	}
	
	operand = *((char *)StackPeek(calc->op_stack));

	/* If the priority of the new operator is higher then the one at the	*/
	/* to of the op_stack, push the new operator							*/
	if (calc->operators[new_str].priority >
		calc->operators[*((unsigned char *)StackPeek(calc->op_stack))].priority)
	{
		StackPush(calc->op_stack, (char *)*str);
		
		return;
	}
	
	/* Else calculate using the operator on the top of the op_stack */
	else
	{
		while (!StackIsEmpty(calc->op_stack))
		{
			if (calc->operators[new_str].priority >
				calc->operators[*((unsigned char *)StackPeek(calc->
				op_stack))].priority)
			{
				StackPush(calc->op_stack, (char *)*str);
		
				return;
			}
			
			if ('(' == *((char *)StackPeek(calc->op_stack)))
			{
				StackPush(calc->op_stack, (char *)*str);
		
				return;
			}
			operand = *((char *)StackPeek(calc->op_stack));
			num2 = *((double *)StackPeek(calc->num_stack));
		
			free(StackPeek(calc->num_stack));
			StackPop(calc->num_stack);
		
			StackPop(calc->op_stack);
			*status = calc->operators[operand].
									calc_func(StackPeek(calc->num_stack), num2);
			
		}
		/* Insert the next operator to the operation stack */
		StackPush(calc->op_stack, (char *)*str);
		
		return;
	}
}

static void OpenBracketHandler(const char **str, status_t *status, calc_t *calc)
{
	assert(str);
	assert(status);
	assert(calc);

	StackPush(calc->op_stack, (char *)*str);
	
	*status = SUCCESS;
}

static void CloseBracketHandler(const char **str, status_t *status,
								calc_t *calc)
{
	unsigned char operand = 0;
	double num2 = 0;

	assert(str);
	assert(status);
	assert(calc);

	UNUSED(**str);
	
	while ('(' != *((char *)StackPeek(calc->op_stack)))
	{	
		operand = *((char *)StackPeek(calc->op_stack));
		num2 = *((double *)StackPeek(calc->num_stack));
		
		free(StackPeek(calc->num_stack));
		StackPop(calc->num_stack);
		
		StackPop(calc->op_stack);
		*status = calc->operators[operand].
									calc_func(StackPeek(calc->num_stack), num2);
		
		if (StackIsEmpty(calc->op_stack))
		{
			*status = SYNTAX_ERROR;
			
			return;
		}	
	}
	StackPop(calc->op_stack);
}

static void EndOfStrHandler(const char **str, status_t *status, calc_t *calc)
{
	unsigned char operand = 0;
	double num2 = 0;

	assert(str);
	assert(status);
	assert(calc);

	UNUSED(str);
		
	while (!StackIsEmpty(calc->op_stack))
	{	
		operand = *((char *)StackPeek(calc->op_stack));
		num2 = *((double *)StackPeek(calc->num_stack));
		
		free(StackPeek(calc->num_stack));
		
		StackPop(calc->num_stack);
		StackPop(calc->op_stack);
		*status = calc->operators[operand].calc_func
										(StackPeek(calc->num_stack), num2);
	}	
}

static void EmptyStacks(stack_t *stack1, stack_t *stack2)
{
	assert(stack1);
	assert(stack2);

	while (!StackIsEmpty(stack1))
	{
		StackPop(stack1);
	}
	
	while (!StackIsEmpty(stack2))
	{
		StackPop(stack2);
	}
}

/*****************************************************************************
							Calculations Functions
						******************************/

static status_t Add(double *num1, double num2)
{ 
	assert(num1);

	*num1 = *num1 + num2;
	
	return (SUCCESS);
}

static status_t Sub(double *num1, double num2)
{
	assert(num1);

	*num1 = *num1 - num2;
	
	return (SUCCESS);
}

static status_t Mult(double *num1, double num2)
{
	assert(num1);

	*num1 = *num1 * num2;
	
	return (SUCCESS);
}

static status_t Div(double *num1, double num2)
{
	assert(num1);

	if (0 == num2)
	{
		*num1 = 0;
		return (MATH_ERROR);
	}
	
	*num1 = *num1 / num2;
	
	return (SUCCESS);
}

static status_t Pow(double *num1, double num2)
{
	int i = 0;
	double result = 1;

	assert(num1);
	
	if (num2 < 0)
	{	
		if (*num1 == 0)
		{
			return (MATH_ERROR);
		}
		
		*num1 = 1 / *num1;
		num2 *= (-1);
	}
	
	for (i = 0; i < num2; ++i)
	{
		result *= *num1;
	} 

	*num1 = result;
	
	return (SUCCESS);
}







