//An Nguyen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

//#define MAX_INPUT 256

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(T*D)


Worst case to do an unsuccessful binary search in a dinctionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(MAX_LEN* log D)
*/

/* You can write helper functions here */

int min(int a,int b, int c){
    int temp;
    temp = a<b?a:b;
    temp = temp<c?temp:c;
    return temp;
}

int findMin(int arr[], int N)
{
    int min = INT_MAX, i;
    for (i = 0; i < N; i++) { 
        if (arr[i] < min) { 
            min = arr[i]; 
        } 
    }

    return min; 
}

int cmpstr(const void* a, const void* b) {
    const char* aa = (const char*)a;
    const char* bb = (const char*)b;

    return strcmp(aa, bb);
}

int binarySearch(int arrSize, char arr[][MAX_INPUT], char *target, int *count)
{
    int left = 0;
    int mid;
    int right = arrSize - 1;
    *count = 0;
    
    while(left <= right)
    {
        *count= *count + 1;
        mid = (right + left)/2;

        int res;
        if(strcmp(arr[mid], target)==0)
        {
            res = mid + 1;
            return mid;
        }
        else if(strcmp(arr[mid], target) > 0){
            right = mid - 1;
        }
        else if(strcmp(arr[mid], target) < 0)
        {
            left = mid + 1;
        }
    }

    return -1;
}

int edit_distance(char * string1, char * string2, int print_table){

	int len1=strlen(string1), len2=strlen(string2);
    int table[len1+2][len2+2], i, j, k;
    
    for(i=0; i<len1+1; i++)
        table[(len1+2)-i][0] = string1[len1-(i)];

    for(j=0; j<len2+3; j++)
    {
        if(j > len2)
        {
            table[0][(len2+2)-j] = 32;
        }
        else
        {
            table[0][(len2+2)-j] = string2[len2-(j)];
        }
    }

    for(i=1;i<len1+2;i++)
        table[i][1] = i-1;

    for(j=0; j<len2+2; j++)
    {
        if(j == 0)
        {
            table[1][j] = 32;
        }
        else
        {
            table[1][j] = j-1;
        }
    }
    
    for(i=0; i<len1; i++)
    {
        for(j=0;j<len2;j++)
        {
            if(string1[i]!=string2[j])
                table[i+2][j+2] = 1 + min(table[i+1][j+2],table[i+2][j+1],table[i+1][j+1]); // i+1,j+1 i+1,j+2, j+2,i+1
            else 
                table[i+2][j+2] = table[i+1][j+1];
        }
    }

    if(print_table)
    {
        for(i=0;i<len1+2;i++)
        {
            for(j=0;j<len2+2;j++)
            {
                if(i==0 || j==0)
                {   
                    printf(" %c|", table[i][j]);
                }
                else
                {
                    printf(" %d|", table[i][j]);
                }
            }
            printf("\n");
            for(k=0; k<len1+2; k++)
            {
                printf("--");
            }
            printf("-\n");
        }
    }

    return table[len1+1][len2+1];
}

void spell_check(char * testname, char * dictname, int printOn){
    FILE *dictFile = NULL;
    FILE *textFile = NULL;
    FILE *outFile = NULL;
    char c, line[MAX_INPUT];
    char outputname[101];
    int i = 0;

    printf("Corrected output file name: ");
    scanf("%s%c", outputname, &c);

    dictFile = fopen(dictname, "r");
    if(dictFile == NULL)
    {
        printf("Dictionary file could not be opened.\n");
        return;
    }

    textFile = fopen(testname, "r");
    if(textFile == NULL)
    {
        printf("Text file could not be opened.\n");
        return;
    }

    outFile = fopen(outputname, "w");
    if(outFile == NULL)
    {
        printf("Output file could not be opened.\n");
        return;
    }

    //LOAD IN DICTIONARY FILE

    int dictSize;
    fscanf(dictFile, "%d", &dictSize);
    
    char wordlist[dictSize][MAX_INPUT];

    printf("\nLoading the dictionary file: %s\n", dictname);

    printf("\nDictionary has size: %d\n", dictSize);

    for(i = 0; i < dictSize; i ++)
    {
        fscanf(dictFile, "%s", line);
        strcpy(wordlist[i], line);
    }

    /*for(i=0; i< dictSize; i++)
    {
        printf("%s\n", wordlist[i]);
    }*/

    if(dictSize > 0)
        qsort(wordlist, dictSize, sizeof(wordlist[0]), cmpstr);

    /*for(i=0; i< dictSize; i++)
    {
        printf("%s\n", wordlist[i]);
    }*/

    //LOAD IN TEXT FILE

    char *textlist;
    if(textFile)
    {
        while ((fgets(line, MAX_INPUT, textFile)!= NULL));
    }


    char *token, *sep;
    char separators[] = " ,.!?";
    int distArr[dictSize]; // keep track of edit distances for each word
    int count, curIndex = 0;
    char linecpy[MAX_INPUT];
    int linelength = strlen(line);
    
    strcpy(linecpy, line);

    token = strtok(line, separators);
    while(token != NULL)
    {
        int wordlen = strlen(token);
        char *lowertoken = (char*) malloc(sizeof(token));

        strcpy(lowertoken, token);
        for(int i = 0 ; token[i]; i++)
        {
            lowertoken[i] = tolower(token[i]);
        }
        int idx = binarySearch(dictSize, wordlist, lowertoken, &count);

        if(idx == -1) // if word is NOT found in dictionary list
        {
            printf("---> |%s| (words compared when searching: %d)\n", token, count); 
            printf("-1 - type correction\n");
            printf(" 0 - leave word as is (do not fix spelling)\n");

            //Computer edit distance between mispelled word and all dictionary words
            for(i = 0; i < dictSize; i++)
            {
                distArr[i] = edit_distance(lowertoken, wordlist[i], 0); // 0 indicates not printing table
            }

            int min = findMin(distArr, dictSize);
            printf("     Minimum distance: %d (computed edit distances: %d)\n", min, dictSize);
            printf("     Words that give minimum distance:\n");

            int l = 1;
            for(i=0; i<dictSize ; i++)
            {
                if(distArr[i] == min)
                {
                    printf(" %d - %s\n", (l++), wordlist[i]);
                }
            }

            char minWords[l][MAX_INPUT];
            l = 0;
            for(i=0; i<dictSize ; i++)
            {
                if(distArr[i] == min)
                {
                    strcpy(minWords[l++], wordlist[i]);
                }
            }

            int input;
            char correctword[MAX_INPUT];
            printf("Enter your choice (from the above options): ");
            scanf("%d", &input);

            if(input == -1)
            {
                printf("Enter correct word: ");
                scanf("%s", correctword);
                fprintf(outFile, "%s", correctword);
            }
            else if(input == 0)
            {
                fprintf(outFile, "%s", token);

            }
            else
            {
                if(input <= l)
                {
                    fprintf(outFile, "%s", minWords[input - 1]);
                }
                else
                {
                    printf("Input out of range");
                    return;
                }
            }
        }
        else
        {
            printf("---> |%s| (words compared when searching: %d)\n", token, count); 
            printf("- OK \n\n");

            fprintf(outFile, "%s", token);
        }

        sep = strstr(linecpy, token);
        sep = sep + strlen(token);

        if(strcmp(sep, "\0") != 0)
        {
            fprintf(outFile, "%c", sep[0]);
        }
        
        if(strcmp(sep, "\0") != 0 && (*(sep+1) == ' '))
        {
            fprintf(outFile, "%c", sep[1]);
        }

        printf("\n");
        token = strtok(NULL, separators);
        free(lowertoken);
    }

    //free(token);
    fclose(dictFile);
    fclose(textFile);
    fclose(outFile);
    return;
}

/*int main()
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
}*/
