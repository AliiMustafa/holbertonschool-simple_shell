#include "main.h"
/**
 * main - function
 * Return: Always 0
 */
int main(void)
{
	char *buf, *token, *commands[100], *trimmed, *path;
	size_t count, i;
	int status = 0;

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
		while (token)
			commands[i] = token, token = strtok(NULL, " \n"), i++;
		commands[i] = NULL;
		built_in_exit(commands, buf, &status);
		if (strcmp(commands[0], "env") == 0)
		{
			free(buf), print_env();
			continue;
		}
		path = handle_path(commands[0]);
		if (strcmp(path, "N_F") == 0)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", commands[0]);
			free(buf), exit(127);
		}
		_fork(path, buf, commands, &status);
		free(path), free(buf);
	}
	return (0);
}
