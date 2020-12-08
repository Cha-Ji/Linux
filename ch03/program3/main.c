#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAXLINE 100

char line[MAXLINE];
char longest[MAXLINE];

int main(){
	int len;
	int max;

	max = 0;
	while(1){
		fgets(line, sizeof(line),stdin);
		len = strlen(line);
		if (len == 1)
			break;
		if (len > max){
			max = len;
			copy(line, longest);
		}
	}
	
	if (max > 0)
		printf("%s", longest);
	

	return 0;
}



	
