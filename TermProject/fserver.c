#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <ctype.h>
#include <unistd.h>

#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int readLine(int fd, char* str) {
	int n;
	do {
		n = read(fd, str, 1);
	} while (n > 0 && *str++ != '\0');
	return(n > 0);
}

int main(int argc, char* argv[]) {
	int sfd, cfd, port, clientlen;
	FILE *fp;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_in serveraddr, clientaddr;
	struct hostent *hp;
	char *haddrp;

	signal(SIGCHLD, SIG_IGN);

	if (argc != 2) {
		fprintf(stderr, "사용법: %s <port>\n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);
	bind(sfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
	listen(sfd, 5);

	while (1) {
		clientlen = sizeof(clientaddr);
		cfd = accept(sfd, (struct sockaddr *)&clientaddr, &clientlen);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		printf("서버: %s(%d)에 연결됨\n", haddrp, clientaddr.sin_port);

		if (fork() == 0) {
			readLine(cfd, inmsg);
			fp = fopen(inmsg, "r");
			if (fp == NULL) {
				write(cfd, "해당 파일 없음", 10);
			}
			else {
				while (fgets(outmsg, MAXLINE, fp) != NULL)
					write(cfd, outmsg, strlen(outmsg) + 1);
			}
			close(cfd);
			exit(0);
		}
		else close(cfd);
	}
}

