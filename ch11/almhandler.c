#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alaramHandler(int signo);

int main(){
	int sec = 0;

	signal(SIGALRM, alaramHandler);
	alarm(5);
	printf("loop\n");
	while(1){
		sleep(1);
		printf("%d sec...\n", ++sec);
	}
	printf("fail!\n");
}

void alaramHandler(int signo){
	printf("get up\n");
	exit(0);
}
