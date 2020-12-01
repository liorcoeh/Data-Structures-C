/*
 * Task
 */

#ifndef TASK_H
#define TASK_H

#include <stddef.h> /* size_t */
#include <time.h>   /* time_t */

#include "uid.h"

typedef struct task task_t;

/******************************************************************************/

/* 
* Task Create: allocate memory and create task struct with client parameters
* Receive: size_t interval - seconds between task executions. 0 for 1 time only
*                            the first occuronce of the task is after the 
*                            interval.
*          pointer to operation_func:
*               * Receive: pointer to void paramter
*               * Return: 0 for success, any other int for failure
*          pointer to void param - to sent to func
* Return: pointer to a new task_t struct			  
* Errors: return NULL if can't allocate memory 		    	  
* Time Complexity: O(1) 
*/
task_t *TaskCreate(size_t interval, int (*operation_func)(void *param),
                   void *param);

/* 
* Task Destroy: destroy the task and free its memory
* Recieve: pointer to task_t struct  	    	  
* Time Complexity: O(1) 
*/
void TaskDestroy(task_t *task);

/* 
* Task Update Time To Execute: update task next_operation_time to its next occurence
* Receive: pointer to task_t			  
* Time Complexity: O(1) 
*/
void TaskUpdateTimeToExecute(task_t *task);

/* 
* Task Get UID: get task UID
* Receive: pointer to task_t
* Return: Uid_t with task's UID		  
* Time Complexity: O(1) 
*/
Uid_t TaskGetUID(task_t *task);

/* 
* Task Execute: invoke task's function
* Receive: pointer to task_t
* Return: function's return status			  
* Time Complexity: O(1) (depends on the function complexity) 
*/
int TaskExecute(task_t *task);

/* 
* Task Compare Time: compare the next operation time of 2 tasks
* Receive: 2 pointers to task_t
* Return:  1 if task1's time is before task2
*          0 if their time is equal
*          -1 if task2's time is before task1		  
* Time Complexity: O(1)
*/
int TaskCompareTime(const task_t *task1, const task_t *task2);

/* 
* Task Get Operation Time: get task's next operation time
* Receive: pointer to task_t
* Return: time_t with task's next operation time			  
* Time Complexity: O(1) 
*/
time_t TaskGetOperationTime(task_t *task);

#endif /* TASK_H */












