#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char *args[] = {NULL};
	char buffer[BUFFER_SIZE];
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("simple_shell$ ");

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		buffer[strcspn(buffer)] = '\0';

		if (strcmp(buffer, "exit") == 0)
		{
			break;
		}
		args[0] = buffer;
		child_pid = fork();

		if (child_pid == -1)
		{
			fprintf(stderr, "Fork error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				fprintf(stderr, "Command execution error: %s\n", strerror(errno));
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}
	return (EXIT_SUCCESS);
}
