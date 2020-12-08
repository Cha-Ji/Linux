#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/un.h>
#include <unistd.h>
#include <ctype.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

void toUpper(char* in, char* out);
int readLine(int fd, char* str);

//file server program
int main(int argc, char* argv[]){
	int sfd, cfd, port, clientlen;
	FILE *fp;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_in serverAddr, clientAddr;
	struct hostent *hp;
	char *haddrp;

	signal(SIGCHLD, SIG_IGN);

	if(argc != 2){
		fprintf(stderr, "사용법 : %s <port>\n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons((unsigned short)port);
	bind(sfd, (struct sockAddr *) &serverAddr, sizeof(serverAddr));
	listen(sfd, 5);

	while(1){
		clientlen = sizeof(clientAddr);
		cfd = accept(sfd, (struct sockAddr *)&clientAddr, &clientlen);
		haddrp = inet_ntoa(clientAddr.sin_addr);
		printf("서버 : %s(%d)에 연결됨\n", haddrp, clientAddr.sin_port);

		if( fork() == 0){
			readLine(cfd, inmsg);	//소켓에서 파일 이름을 읽는다.
			fp = fopen(inmsg, "r");
			if(fp == '\0'){
				write(cfd, "해당 파일 없음", 10);
			}else{	//파일에서 한 줄 씩 읽어 소켓을 통해 보낸다.
				while(fgets(outmsg, MAXLINE, fp)!= '\0')
					write(cfd, outmsg, strlen(outmsg) + 1);
			}
			close(cfd);
			exit(0);
		}else close(cfd);

	}
}
