#include "main.h"
/**
 * main - entry point
 * Return: always 0
 */
int main(void)
{
	char *buf, *token, *commands[100];
	size_t count = 0;
	ssize_t nread;
	pid_t child;
	int i, status, f = 1;

	while (f)
	{
		buf = NULL;
		nread = getline(&buf, &count, stdin);
		if (nread ==  -1)
			f = 0, free(buf), exit(0);
		token = strtok(buf, " \n");
		i = 0;
		while (token)
		{
			commands[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}
		commands[i] = NULL, child = fork();
		if (child == -1)
			free(buf), perror("Fork failed"), exit(EXIT_FAILURE);
		else if (child == 0)
		{
			if (execve(commands[0], commands, NULL) == -1)
				free(buf), exit(EXIT_FAILURE);
		}
		else
		{
			if (wait(&status) == -1)
				free(buf), perror("Wait failed"), exit(EXIT_FAILURE);
		}
		free(buf);
	}
	return (0);
}

