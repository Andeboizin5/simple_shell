#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point
 * Return: Always 0
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	char *args[2];
	ssize_t read_bytes;
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

	read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	if (read_bytes == 0)
	{
		printf("\n");
		break;
	}
	if (read_bytes == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

	buffer[read_bytes - 1] = '\0';

	args[0] = buffer;
	args[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else
	{
		waitpid(child_pid, &status, 0);
	}
	}
	return (EXIT_SUCCESS);
}
