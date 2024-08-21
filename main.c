#include "main.h"

int main(void)
{
<<<<<<< HEAD
	char *buf, *token, *commands[100], *trimmed;
	size_t count, i;
	pid_t child;
	int status;

	while (1)
	{
		i = 0, buf = NULL;
		if (getline(&buf, &count, stdin) == -1)
			free(buf), exit(0);
		trimmed = trim(buf);
		if (trimmed[0] == '\n')
		{
			free(trimmed), free(buf);
			continue;
		}
		free(trimmed);
		token = strtok(buf, " \n");
		while(token)
		{
			commands[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}
		commands[i] = NULL;
		if (strcmp(commands[i - 1], "exit") == 0)
		{
			free(buf);
			if (i == 1)
				exit(0);
			else
				exit(2);
		}
		child = fork();
		if (child == -1)
			free(buf), perror("Fork failed"), exit(EXIT_FAILURE);
		else if (child == 0)
		{
			if (execve(commands[0], commands, NULL) == -1)
				free(buf), perror("we found error"), exit(0);
		}
		else
		{
			if (wait(&status) == -1)
				free(buf), perror("wait has failed"), exit(0);
		}
		free(buf);
	}

	return (0);
=======
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
>>>>>>> 04f929cd3411501d7190f3387e465f635ac862b4
}
