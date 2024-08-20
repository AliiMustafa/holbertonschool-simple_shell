#include "main.h"
extern char **environ;

int main(void)
{
    char *buf = NULL, *token;
    size_t count = 0;
    ssize_t nread;
    pid_t child;
    char *commands[100];
    int i, status;
    int f = 1;

    while (f)
    {
        printf("$ ");

        nread = getline(&buf, &count, stdin);
        if (nread == -1)
        {
            free(buf);
            exit(EXIT_SUCCESS);
        }

        // Remove trailing newline if present
        buf[strcspn(buf, "\n")] = '\0';

        token = strtok(buf, " \n");
        i = 0;
        while (token)
        {
            commands[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        commands[i] = NULL;

        child = fork();
        if (child == -1)
        {
            perror("Fork failed");
            free(buf);
            exit(EXIT_FAILURE);
        }
        else if (child == 0)
        {
            if (execve(commands[0], commands, environ) == -1)
            {
                perror("Failed to execute");
                free(buf);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (waitpid(child, &status, 0) == -1)
            {
                perror("Wait failed");
                free(buf);
                exit(EXIT_FAILURE);
            }
        }
    }

    free(buf);
    return 0;
}
