#ifndef SPELL_H
#define	SPELL_H

#include <limits.h>

/*
first_str - first string (vertical)
second_str - second string (horizontal)
print_table - can have value 1 or other.
	Value 1 indicates to print the distance matrix.
	Value 0 indicates to NOT print the distance matrix. In this case
	the function is used only to compute the distance between 2 words.
	You do not have to deal with the other cases (values different than 1 or 0),
	but you can if you want to.
*/
int min(int a,int b,int c);

int findMin(int arr[], int N);

int cmpstr(const void *a, const void *b);

int binarySearch(int arrSize, char arr[][MAX_INPUT], char *target, int *count);

int edit_distance(char * first_str, char * second_str, int print_table);

void spell_check(char * dictname, char * testname, int printOn);

#endif	/* SPELL_H */

