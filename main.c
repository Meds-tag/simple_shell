#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> /* Include sys/wait.h for wait function */

#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ; /* Access to the environment variables */

int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	pid_t pid;
	char *token;
	char *args[256]; /* Maximum arguments count */
	int i;

	buffer = malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	i = 0; /* Initialize i before each iteration */

	while (1)
	{
		printf("$ ");
		if (getline(&buffer, &bufsize, stdin) == -1)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		buffer[strcspn(buffer, "\n")] = '\0';

		token = strtok(buffer, DELIMITERS);
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, DELIMITERS);
		}
		args[i] = NULL; /* Mark the end of arguments with NULL */

		if (strcmp(args[0], "exit") == 0)
		{
			break; /* Exit the shell */
		}
		else if (strcmp(args[0], "env") == 0)
		{
			/* Print environment variables */
			char **env = environ;
			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			continue; /* Continue to prompt for input */
		}

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			/* Child process */
			if (execve(args[0], args, NULL) == -1)
			{
				perror(args[0]);
				free(buffer);
				exit(EXIT_FAILURE); /* Terminate child process if execve fails */
			}
		}
		else
		{
			/* Parent process */
			wait(NULL);
		}

		i = 0; /* Reset i for next iteration */
	}

	free(buffer);
	return (0);
}
