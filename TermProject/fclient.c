#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

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
	int sfd, port, result;
	char *host, inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_in serverAddr;
	struct hostent *hp;

	if (argc != 3) {
		fprintf(stderr, "사용법: %s <host> <port> \n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = atoi(argv[2]);

	sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	if ((hp = gethostbyname(host)) == NULL)
		perror("gethostbyname error");
	bzero((char*)&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	bcopy((char *)hp->h_addr_list[0],
		(char *)&serverAddr.sin_addr.s_addr, hp->h_length);
	serverAddr.sin_port = htons(port);

	do {
		result = connect(sfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
		if (result == -1) sleep(1);
	} while (result == -1);

	printf("다운로드할 파일 이름 입력 : ");
	scanf("%s", inmsg);
	write(sfd, inmsg, strlen(inmsg) + 1);

	/*    check      */
	FILE *wfile = fopen(inmsg, "w");

	while (readLine(sfd, outmsg)){
		printf("%s", outmsg);
		fputs(outmsg, wfile);
		// fwrite(outmsg, strlen(outmsg), 1, wfile);
	}
	fclose(wfile);
	close(sfd);
	exit(0);
}

