#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[]){
	struct student rec;
	char c;
	int id;
	FILE *fp;

	if(argc != 2){
		fprintf(stderr, "사용법: %s 파일이름 \n",argv[0]);
		return 1;
	}

	if ((fp = fopen(argv[1], "rb")) == NULL){
		fprintf(stderr, "파일 열기 오류\n");
		return 2;
	}

	do{
		printf("검색할 학생의 학번 입력: ");
		if (scanf("%d", &id) == 1){
			fseek(fp, (id - START_ID) * sizeof(rec), SEEK_SET);
			if((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0))
				printf("학번: %8d 이름: %4s 점수: %4d\n",
						rec.id, rec.name, rec.score);
			else printf("no record %d\n", id);
		}
		else printf("input error");

		printf("continue?(Y/N)");
		scanf("%s", &c);
	}while(c == 'Y');

	fclose(fp);
	return 0;
}




