#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "common.h"

int check_arg(char *av[], const char *opt)
{
	int count = 0;

	while(*av != '\0')
	{
		
		if(!strcmp(av[count], opt))
		{
			return TRUE;
		}

		av++;
	}

	return FALSE;
}

void cmd_cd(int ac, char *av[])
{
	char *path;

	if(ac > 1)
	{
		path = av[1];
	}

	else if((path = (char*)getenv("HOME")) == NULL)
	{

		path = ".";
	}


	if(chdir(path) == ERROR)
	{
		fprintf(stderr, "%s: bad directory.\n", path);
	}
}




