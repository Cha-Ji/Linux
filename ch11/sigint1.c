#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void intHandler(int signo);

int main(){
	signal(SIGINT, intHandler);

	while(1)
		pause();

	printf("fail!\n");
}

void intHandler(int signo){
	printf("interupt handle\n");
	printf("sig num : %d\n", signo);
	exit(0);
}
