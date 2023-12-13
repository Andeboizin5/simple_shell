#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buffer[BUFFER_SIZE];
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		if (!fgets(buffer, BUFFER_SIZE, stdin))
		{
			printf("\n");
			break;
		}

		buffer[strcspn(buffer, "\n")] = 0;

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error forking");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{
			if (execve(buffer, NULL, NULL) == -1)
			{
				perror("Execution error");
				exit(EXIT_FAILURE);
			}
		} else
		{
			waitpid(child_pid, &status, 0);
		}
	}
	return (EXIT_SUCCESS);
}

