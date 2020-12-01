/*
 * UID
 */

#ifndef UID_H
#define UID_H

#include <time.h>      /* time_t */
#include <sys/types.h> /* pid_t */

typedef struct uid
{
    pid_t pid;
    time_t time;
    size_t count;
} Uid_t;

/******************************************************************************/

/* 
* UID Create: create new UID		
* Return: Uid_t new UID			  
* Time Complexity: O(1) 
*/
Uid_t UIDCreate();

/* 
* UID Get Bad: create bad UID - every bad UID's are equal		
* Return: Uid_t bad UID			  
* Time Complexity: O(1) 
*/
Uid_t UIDGetBadUID();

/* 
* UID Is Same: check if 2 UID's are the same		
* Return: 1 if they are the same, 0 if not			  
* Time Complexity: O(1) 
*/
int UIDIsSame(Uid_t first, Uid_t second);

#endif /* UID_H */














