#include <stdio.h>
#include "print.h"
#include "word.h"
int main(){
	
	char name[20];
	scanf("%s", name);
	printfile(name);
	wc(name);

	return 0;
}
