#include <stdio.h>
#include <string.h>

void wc(char* fileName){
	FILE *fp;
	char myString[150];
	fp = fopen(fileName, "r");

	int lineCount = 0;
	int charCount = 0;
	int wordCount = 0;
	while(fgets(myString, 100, fp) != NULL){
		lineCount ++;
		charCount += strlen(myString);
		for(int i=0; i<strlen(myString);i++)
			if (myString[i] == ' ')
				wordCount ++;
	}
	printf("word Count : %d\n",wordCount);
	printf("char Count : %d\n",charCount);
	printf("line Count : %d\n",lineCount);
	fclose(fp);
}
