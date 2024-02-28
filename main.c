#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> /* Include sys/wait.h for wait function */

#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

void execute_command(char *args[]);
void print_environment();
void free_buffer(char *buffer);

int main(void)
{
    char *buffer;
    size_t bufsize = BUFFER_SIZE;

    buffer = malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    while (1)
    {
        printf("$ ");
        if (getline(&buffer, &bufsize, stdin) == -1)
        {
            free_buffer(buffer);
            exit(EXIT_SUCCESS);
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        char *token;
        char *args[256]; /* Maximum arguments count */
        int i = 0;       /* Initialize i before each iteration */

        token = strtok(buffer, DELIMITERS);
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, DELIMITERS);
        }
        args[i] = NULL; /* Mark the end of arguments with NULL */

        if (strcmp(args[0], "exit") == 0)
        {
            free_buffer(buffer);
            exit(EXIT_SUCCESS); /* Exit the shell */
        }
        else if (strcmp(args[0], "env") == 0)
        {
            print_environment();
        }
        else
        {
            execute_command(args);
        }
    }

    free_buffer(buffer);
    return 0;
}

void execute_command(char *args[])
{
    pid_t pid = fork();

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
            exit(EXIT_FAILURE); /* Terminate child process if execve fails */
        }
    }
    else
    {
        /* Parent process */
        wait(NULL);
    }
}

void print_environment()
{
    char **env = environ;
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

void free_buffer(char *buffer)
{
    if (buffer != NULL)
    {
        free(buffer);
    }
}
