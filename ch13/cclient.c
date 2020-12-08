#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int readLine(int fd, char* str);

int main(){
	int sfd, result;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_un serverAddr;

	sfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverAddr.sun_family = AF_UNIX;
	strcpy(serverAddr.sun_path, "convert");

	do{
		result = connect(sfd, (struct sockaddr *)&serverAddr, 
						sizeof(serverAddr));
		if(result == -1) sleep(1);
	}while(result == -1);

	printf("반환할 문자열 입력:\n");
	fgets(inmsg, MAXLINE, stdin);
	write(sfd, inmsg, strlen(inmsg) + 1);

	readLine(sfd, outmsg);
	printf("%s --> \n%s", inmsg, outmsg);
	close(sfd);
	exit(0);
}

int readLine(int fd, char* str){
	int n;
	do{
		n = read(fd, str, 1);
	}while(n > 0 && *str++ != '\0');
		return (n > 0);
}














