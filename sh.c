#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for execvp
#include "string.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <termios.h>
#include <signal.h>

int main(int ac, char* args[])
{
	signal(SIGINT, SIG_IGN);

	while(1)
	{
		char inputs[50];
		//if( signal(SIGINT, SIG_IGN) != SIG_IGN ) signal(SIGINT, sigIgnore);
		fgets(inputs, sizeof(inputs), stdin);
		int i = 0;
			inputs[strlen(inputs)-1] = '\0';
			if( (strcmp(inputs,"exit")) == 0 ) {exit(1);}
			args[i] = strtok( inputs, " ");
			while( (args[++i] = strtok(NULL," ") ) );

		int forked;
		forked = fork();
		if(forked == -1) {perror("forkErr");}//check4Err

		if( forked == 0 ) // forked at 0 is child, 
		{
			execvp(args[0], args);
			exit(17);
		}
		else // else it is child process
		{
			if( (strcmp(inputs,"cd") ) == 0) chdir( args[1] );
			int childVal;
			int waitVal;
			waitVal = wait(&childVal);
		}
	}
	return 0;
}

























