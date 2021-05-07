#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spell.h"

/*
Repeatedly read 2 strings from the user.
The strings must be separated by a space.
The program will compute the edit distance between them,
print the cost table, the cost and the alignment.

After that, read 2 file names (one for a dictionary file and
one for a file to be spell-checked); spell-check all the words in the text file
and write the corrected text to an output file.
*/


int main()
{
  // any word or file name can be at most 100 characters.
  char first[101],second[101], dictname[101], testname[101];
  char c;
  int  printOn = 0;  // print-off


  // Part1: Compute and show edit distance for pairs of words
  printf("Repeatedly enter two words separated by a space (e.g.: cat someone).\n Stop with: -1 -1\n");
  while (1==1) {
	scanf("%s %s%c", first, second, &c);
	printf("\n first: %s\n", first);
	printf("second: %s\n", second);
	if (strcmp(first,"-1") == 0 && strcmp(second,"-1") == 0) {
		break;
	}
	else {
		int dist = edit_distance(first, second, 1);  // last argument, 1, indicates that the distance table should be printed
		printf("edit distance: %d\n", dist);
		printf("\n=========================================================================================\n");
	}
  }

  // Part2: read filenames and call spell-check
  printf("\nPart 2 - spell check a file.");
  printf("\nEnter print mode (0 - not verbose, 1 - verbose): ");
  scanf("%d", &printOn); // printf("Enter the dictionary file name: ");

  printf("Enter the dictionary file name: ");
  scanf("%s%c", dictname, &c);
  printf("Enter the text file name: ");
  scanf("%s%c", testname, &c);
  spell_check(testname, dictname, printOn);

  return 0;
}
