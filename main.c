#include "main.h"
int main(void)
{
        char *buf, *token;
        size_t count = 0;
        ssize_t nread;
        pid_t child;
        char **commands;
	int i, status;

        while (1)
        {
		buf = NULL;

                nread = getline(&buf, &count, stdin);

                if (nread ==  -1)
                {
			free(buf);
                        exit(0);
                }
                token = strtok(buf, " \n");
                commands = malloc(sizeof(char*) * 1024);
		if (commands == NULL)
		{
			perror("Malloc fail");
			exit(1);
		}
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
			free(buf);
			free(commands);
                        perror("Fork failed");
			exit(EXIT_FAILURE);
                }
		else if (child == 0)
                {
                        if (execve(commands[0], commands, NULL) == -1)
                        {
                                perror("Failed to execute");
                                exit(97);
                        }
                	wait(&status);
		}
        }
	free(commands);
        free(buf);
        return (0);
}

