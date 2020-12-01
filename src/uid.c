/*
 * UID - Functions Definitions
 */

#include <unistd.h>		/* getpid() */
#include <pthread.h>	/* pthread functions */

#include "uid.h"

/******************************************************************************/
/******************************************************************************
								  MAIN FUNCTIONS
							*************************/

Uid_t UIDCreate()
{
	Uid_t new_uid;
	static size_t count = 0;

	pthread_mutex_t lock;
	pthread_mutex_init(&lock, NULL);

	new_uid.pid = getpid();
	new_uid.time = time(NULL);

	pthread_mutex_lock(&lock);
	new_uid.count = count;

	++count;
	pthread_mutex_unlock(&lock);

	return (new_uid);
}

/******************************************************************************/

Uid_t UIDGetBadUID()
{
	Uid_t bad_uid;

	bad_uid.pid = 0;
	bad_uid.time = 0;
	bad_uid.count = 0;

	return (bad_uid);
}

/******************************************************************************/

int UIDIsSame(Uid_t first, Uid_t second)
{
	return (first.pid == second.pid &&
			first.time == second.time &&
			first.count == second.count);
}










