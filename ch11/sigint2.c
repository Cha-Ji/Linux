#include <stdio.h>
#include <signal.h>
#include <unistd.h>

struct sigaction newact;
struct sigaction oldact;
void sigint_handler(int signo);

int main(void){
	newact.sa_handler = sigint_handler;
	sigfillset(&newact.sa_mask);

	sigaction(SIGINT, &newact, &oldact);
	while(1){
		printf("press Ctrl-C !\n");
		sleep(1);
	}
}

void sigint_handler(int signo){
	printf("%d 번 시그널 처리!\n", signo);
	printf("또 누르면 종료됩니다.\n");
	sigaction(SIGINT, &oldact, NULL);
}
