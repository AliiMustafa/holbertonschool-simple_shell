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
                write(STDOUT_FILENO, "OurShell$ ", 10);
		buf = NULL;

                nread = getline(&buf, &count, stdin);

                if (nread ==  -1)
                {
                        perror("Exitting shell");
                        exit(1);
                }
                token = strtok(buf, " \n");
                commands = malloc(sizeof(char*) * 1024);
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
                        perror("Exitting shell");
			exit(41);
                }
                if (child == 0)
                {
                        if (execve(commands[0], commands, NULL) == -1)
                        {
                                perror("Failed to execute");
                                exit(97);
                        }
			exit(1);

                }
                wait(&status);
        }
        free(buf);
        return (0);
}

