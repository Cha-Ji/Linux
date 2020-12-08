#include <stdio.h>

void printfile (char* fileName){
	FILE *fp;
	char myString[150];
	fp = fopen (fileName, "r");

	while (fgets (myString, 100, fp) != NULL){
		puts (myString);
	}

	fclose (fp);
}
