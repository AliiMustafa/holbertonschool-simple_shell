#include "main.h"
/**
 * main - entry
 * Return: Always 0
 */
int main(void)
{
	char *buf, *token, *commands[100], *trimmed, *path;
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
		free(trimmed), token = strtok(buf, " \n");
		while(token)
		{
			commands[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}
		commands[i] = NULL;
		path = handle_path(commands[0]);
		if (strcmp(path, "N_F") == 0)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", commands[0]);
			free(buf);
			exit(127);
		}
		child = fork();
		if (child == -1)
			free(path), free(buf), perror("Fork failed"), exit(EXIT_FAILURE);
		else if (child == 0)
		{
			if (execve(path, commands, NULL) == -1)
				free(path), free(buf), perror("we found error"), exit(0);
		}
		else
		{
			if (wait(&status) == -1)
				free(path), free(buf), perror("wait has failed"), exit(0);
		}
		free(path);
		free(buf);
	}

	return (0);
}
