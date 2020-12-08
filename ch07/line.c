#include <stdio.h>
#define MAXLINE 80

int main(int argc, char *argv[]){
	FILE *fp;
	int line = 0;
	char buffer[MAXLINE];

	if(argc != 2){
		fprintf(stderr, "사용법 : line 파일이름\n");
		return 2;
	}

	if ((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "fopen error!\n");
		return 2;
	}


	while(fgets(buffer, MAXLINE, fp) != NULL){
		line++;
		printf("%3d %s", line, buffer);
	}

	return 0;
}
