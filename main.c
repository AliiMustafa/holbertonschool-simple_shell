#include "main.h"

int main(void)
{
    char *buf = NULL, *token, *commands[100];
    size_t count = 0;
    ssize_t nread;
    pid_t child;
    int i, status;
    int f = 1;

    while (f)
    {
        buf = NULL;
        nread = getline(&buf, &count, stdin);
        if (nread == -1)
        {
            free(buf);
            exit(0);
        }

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
            if (execve(commands[0], commands, NULL) == -1)
            {
                perror("Execution failed");
                free(buf);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (wait(&status) == -1)
            {
                perror("Wait failed");
                free(buf);
                exit(EXIT_FAILURE);
            }
	    	free(buf);
                buf = NULL;
        }

    }

    return 0;
}
