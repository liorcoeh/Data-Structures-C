/*
 * UID - Test File
 */

#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep */

#include "uid.h"

int main()
{
	Uid_t new_uid;
	Uid_t new_uid2;
	Uid_t new_uid3;

	new_uid = UIDCreate();
	printf("\nUID 1:\n");
	printf("pid %d\n", new_uid.pid);
	printf("time %ld\n", new_uid.time);
	printf("count %ld\n", new_uid.count);

	sleep(2);

	new_uid2 = UIDCreate();
	printf("\nUID 2:\n");
	printf("pid %d\n", new_uid2.pid);
	printf("time %ld\n", new_uid2.time);
	printf("count %ld\n", new_uid2.count);

	sleep(2);

	new_uid3 = UIDGetBadUID();

	printf("\nUID 3 - bad one:\n");
	printf("pid %d\n", new_uid3.pid);
	printf("time %ld\n", new_uid3.time);
	printf("count %ld\n", new_uid3.count);

	printf("\n Is UID 1 & 2 are the same? %d\n", UIDIsSame(new_uid, new_uid2));

	printf("\n Is UID 1 & 1 are the same? %d\n", UIDIsSame(new_uid, new_uid));
	return (0);
}















