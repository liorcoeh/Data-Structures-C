/*
 * Scheduler
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stddef.h> /* size_t */
#include "uid.h"    /* Uid_t */

typedef struct scheduler scheduler_t;

/******************************************************************************/

/* 
* Scheduler Create: allocate memory and create scheduler struct.
* Return: pointer to a new scheduler_t struct.
* Errors: return NULL if an error occured.	    	  
* Time Complexity: O(1) 
*/
scheduler_t *SchedulerCreate();

/* 
* Scheduler Destroy: destroy the scheduler and free its memory.
* Recieve: pointer to scheduler_t struct.
* Time Complexity: O(n)
*/
void SchedulerDestroy(scheduler_t *schd);

/* 
* Scheduler Run: run the scheduler.
* Receive: pointer to scheduler_t struct.
* Return: 0 if function stopped by command.
*         1 if no tasks left.
*         2 if an internal scheduler error occured.
*/
int SchedulerRun(scheduler_t *schd);

/* 
* Scheduler Stop: stops the scheduler.
* Receive: pointer to scheduler_t struct.
*/
void SchedulerStop(scheduler_t *schd);

/* 
* Scheduler Insert Task: insert new task to the scheduler.
* Receive: schd - pointer to scheduler_t struct.
*          interval - interval between invocations in seconds.
*          operation_func -
*               * Receive: pointer to void paramter.
*               * Return: 0 for success, any other int for failure.
*          param - to sent to operation_func.
* Return: Uid_t with the UID of the task.
* Errors: Return bad UID if error occured
* Time Complexity: O(n)
*/
Uid_t SchedulerInsertTask(scheduler_t *schd,
                          size_t interval,
                          int (*operation_func)(void *param),
                          void *param);

/* 
* Scheduler Insert Task: remove task from the scheduler
* Receive: pointer to scheduler_t struct
*          Uid_t of the task to remove
* Return: 0 if found the uid and removed, 1 if not
* Time Complexity: O(n)
*/
int SchedulerRemoveTask(scheduler_t *schd, Uid_t uid);

/* 
* Scheduler Size: get scheduler size
* Receive: pointer to scheduler_t struct
* Return: size_t with the size of the scheduler
* Time Complexity: O(n)
*/
size_t SchedulerSize(const scheduler_t *schd);

/* 
* Scheduler Is Empty: check if scheduler is empty
* Receive: pointer to scheduler_t struct
* Return: 1 if empty, 0 if not
* Time Complexity: O(1)
*/
int SchedulerIsEmpty(const scheduler_t *schd);

/* 
* Scheduler Clear: clear scheduler - remove all its tasks
* Receive: pointer to scheduler_t struct
* Time Complexity: O(n)
*/
void SchedulerClear(scheduler_t *schd);

#endif /* SCHEDULER_H */







