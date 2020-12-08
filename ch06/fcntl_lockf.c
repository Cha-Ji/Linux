//fcntl() => lockf()

//int lockf(int fd, int cmd, off_t len)
//fcntl(fd, F_SETLKW, &lock)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int lockf(int fd, int cmd, off_t len){
	lock.l_type = F_SETLK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (id - START_ID)*sizeof(rec);
	lock.l_len = sizeof(rec);

	if(fcntl(fd, F_SETLK, &lock) == -1){
		perror(argv[1]);
		exit(3);
	}
	
	lseek(fd, (id-START_ID)*sizeof(rec), SEEK_SET);
}
