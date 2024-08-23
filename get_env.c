#include "main.h"
char *get_env(char *path)
{
	int i = 0;
	char **env;
	char *token, *cpy, *result;

	env = environ;
	while (env[i])
	{
		cpy = strdup(env[i]);
		if (!cpy)
			return ("(null)");
		token = strtok(cpy, "=");
		if (strcmp(token, path) == 0)
		{
			token = strtok(NULL, "\n");
			if (token == NULL)
			{
				free(cpy);
				return ("(null)");
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
