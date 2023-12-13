#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point
 * Return: Always 0
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	char *args[2];
	ssize_t read_chars;
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");

		if ((read_chars = read(STDIN_FILENO, buffer, BUFFER_SIZE)) == -1)
		{
			perror("read");
			return (EXIT_FAILURE);
		}

		if (read_chars == 0)
		{
			printf("\n");
			break;
		}

		buffer[read_chars - 1] = '\0';
		args[0] = buffer;
		args[1] = NULL;

		if ((child_pid = fork()) == -1)
		{
			perror("fork");
			return EXIT_FAILURE;
		}

		if (child_pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve");
				return EXIT_FAILURE;
			}
		} else {
			waitpid(child_pid, &status, 0);
		}
	}
	return EXIT_SUCCESS;
}
