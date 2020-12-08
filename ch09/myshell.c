#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int system(const char* cmdstring);
int main(){

	char cmdstring[30];
	while(1){
		printf("[Shell] ");
		fgets(cmdstring, sizeof(cmdstring),stdin);
		if(system(cmdstring) == -1)
			perror("error!");
	}
}

int system(const char*cmdstring){
	int pid, status;

	if(cmdstring == NULL)return 1;
	pid = fork();


	if(pid == -1) return -1;

	if(pid == 0){
		execl("/bin/sh", "sh", "-c", cmdstring,(char*)0);
	_exit(127);
	}

	do{
		if(waitpid(pid, &status, 0) == -1){
			if(errno != EINTR)return -1;
		}else return status;
	}while(1);
}
		




