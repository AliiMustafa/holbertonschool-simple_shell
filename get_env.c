#include "main.h"
char *get_env(char *path, char *command)
{
	int i = 0;
	char **env;
	char *token, *cpy, *result;

	env = environ;
	while (env[i])
	{
		cpy = strdup(env[i]);
		if (!cpy)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", command);
			exit(127);
		}
		token = strtok(cpy, "=");
		if (strcmp(token, path) == 0)
		{
			token = strtok(NULL, "\n");
			if (!token)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", command);
				free(cpy);
				exit(127);
			}
			result = strdup(token);
			free(cpy);
			return (result);
		}
		free(cpy);
		i++;
	}
	return ("(null)");
}
