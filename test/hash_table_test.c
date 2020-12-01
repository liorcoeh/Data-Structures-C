/*
 * Hash Table - Test File
 */

#include <stdio.h> /* printf() */
#include <string.h>	/* strlen() */
#include <stdlib.h> /* system()	*/

#include "hash_table.h"

#define PRIME_NUM (16769023)
#define SMALL_SIZE (10)
#define SIZE (102305)
#define WORD_SIZE (30)	/* Dictionary word size */

/**************************** User Functions *********************************/

/*
 * Cmp Func: Function to determine where each new node will be inserted
 * Return:
 * - 0 If the new data will be lower than the existing one
 * - 1 If the new data will be higher than the existing one
 * - -1 If both datas are the same
 * - Recieve:
 * - const void * - Pointer to the data that will be inserted
 * - const void * - Pointer to the data to compare to
 * - const void * - Pointer to a parameter which can be used in the function
 * Time Complexity: O(1)
 */
int CmpFunc(const void *first, const void *second);

size_t IntHashFunc(const void *data);
size_t HashFunc(const void *data);

/*
 * Ope Func: Function that changes data inside an element
 * Return: 0 for success, 1 for failure
 * Receive:
 * - const void * - Pointer to the data that will be changed
 * - const void * - Pointer to a parameter which can be used in the function
 * Time Complexity: O(1)
 */
int OprFunc(void *data, const void *param);

/*****************************************************************************/
/*****************************************************************************/

int main()
{
	size_t i = 0;
	int check = 0;
	int param = 1;
	int a = 48;
	int b = 50;
	int c = 30;
	int d = 10;
	char **dictionary = NULL;
	char input[WORD_SIZE] = {0};
	char words[WORD_SIZE] = {0};
	int length = 0;
	FILE *fp;
	hash_t *new_hash = NULL;
	
	/***************************************************************************
								BASIC SIMPLE TEST
	***************************************************************************/
	
	hash_t *main_hash = HashCreate(CmpFunc, IntHashFunc, SMALL_SIZE);
	
	system("clear");
	
	printf("\nAfter creation the hash table is empty (1): ");
	printf("%d\n", HashIsEmpty(main_hash));
	printf("And it's size is (0): %ld\n\n", HashSize(main_hash));
	
	HashInsert(main_hash, &a);
	HashInsert(main_hash, &b);
	HashInsert(main_hash, &c);
	HashInsert(main_hash, &d);
	printf("After four insertions, the hash table is NOT empty (0): ");
	printf("%d\n", HashIsEmpty(main_hash));
	printf("And it's size is (4): %ld\n\n", HashSize(main_hash));
	
	printf("The Hash Load is: %f\n", HashLoad(main_hash));
	printf("And the SD is: %f\n\n", HashSD(main_hash));
	
	printf("Looking to find (%d) data: ", c);
	printf("%d\n\n", *((int *)HashFind(main_hash, &c)));
	
	printf("For Each will print all the elements in the hash table;\n");
	HashForEach(main_hash, OprFunc, &param);
	printf("\n\n");

	HashRemove(main_hash, &a);
	printf("After one remove, the hash table size is (3): ");
	printf("%ld\n", HashSize(main_hash));
	HashForEach(main_hash, OprFunc, &param);
	printf("\n\n");
	
	printf("After two more removes:\n");
	HashRemove(main_hash, &b);
	HashRemove(main_hash, &c);
	printf("The Hash Load is: %f\n", HashLoad(main_hash));
	printf("And the SD is: %f\n\n\n", HashSD(main_hash));
	
	HashDestroy(main_hash);
	
	/***************************************************************************
								DICTIONARY TEST
	***************************************************************************/
	
	new_hash = HashCreate(CmpFunc, HashFunc, SIZE);
	
	dictionary = (char **)malloc(sizeof(char *) * SIZE);
	
	fp = fopen("/usr/share/dict/american-english", "r");
	
	for (i = 0; i < SIZE; ++i)
	{
		fscanf(fp, "%s", words);
		length = strlen(words);
		dictionary[i] = (char *)malloc(sizeof(char) * (length + 1));
		strcpy(dictionary[i], words);
	}
	
	fclose(fp);
	
	for (i = 0; i < SIZE; ++i)
	{
		HashInsert(new_hash, dictionary[i]);
	}
	
	printf("After putting the dictionary, the hash table is NOT empty (0): ");
	printf("%d\n", HashIsEmpty(new_hash));
	printf("And it's size is (%d): %ld\n\n", SIZE, HashSize(new_hash));
	
	printf("The Hash Load is: %f\n", HashLoad(new_hash));
	printf("And the SD is: %f\n", HashSD(new_hash));

	printf("\n\nPress Enter to continue\n");
	fgets(input, 2, stdin);
	system("clear");
	
	while (0 == check)
	{
		printf("\n\n\t\t\tEnter a word to look for, or 'QUIT' to exit\n");
		printf("\t\t\t\t\t\n");
		scanf("%s", input);
		system("clear");
		if (0 == strcmp(input, "QUIT"))
		{
			check = 1;
		}
		else if (NULL == HashFind(new_hash, input))
		{
			printf("\n\n\t\t\t%s\n\n", input);
			printf("\t\t\tWord Not Found\n");
		}
		else
		{
			printf("\n\n\t\t\t%s\n\n", input);
			printf("\t\t\tWord Found\n");
		}	
	}

	for (i = 0; i < SIZE; ++i)
	{
		free(dictionary[i]);
	}
	
	free(dictionary);
	dictionary = NULL;

	HashDestroy(new_hash);

	return (0);
}

/*****************************************************************************/
/*****************************************************************************

								USER FUNCTIONS
							**********************/

int CmpFunc(const void *data1, const void *data2)	
{
	if (0 == strcmp((char *)data1, (char *)data2))
	{
		return (0);
	}
	
	return (1);
}

size_t IntHashFunc(const void *data)
{
	size_t key = *((int *)data);
	
	key = key % SMALL_SIZE;
	
	return (key);
}

size_t HashFunc(const void *data)
{
	char *c = (char *)data;
	size_t key = 1;

	while('\0' != *c)
	{
		key *= PRIME_NUM * (*c);
		++c;
	}
	
	key = key % SIZE;
	
    return (key); 
}
	
int OprFunc(void *data, const void *param)
{
	printf("%d->", *((int *)data) * (*((int *)param)));
	
	return (0);
}	













