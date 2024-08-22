#include "main.h"
/**
 * _strcat - func
 * @str1: pointer
 * @str2: pointer
 * Return: concat of 2 string
 */
char *_strcat(char *str1, char *str2) 
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t total_len = len1 + len2;
	char *result;
	
	result = malloc(total_len + 1);
	if (result == NULL) 
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	strcpy(result, str1);
	strcat(result, str2);
	return (result);
}
/**
 * handle_path - func
 * @command: pointer
 * Return: pointer
 */
char *handle_path(char *command)
{
	char *direc, *token, *d, *c;

	if (access(command, X_OK) == 0)
	{
		c = malloc(sizeof(char) * (strlen(command) + 1));
		strcpy(c, command);
		return (c);
	}
	command = _strcat("/", command);
	if (!command)
	{
		perror("Failed to concat");
		exit(EXIT_FAILURE);
	}
	direc = get_env("PATH");
	if (!direc)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		free(command);
		exit(127);
	}
	d = malloc(sizeof(char) * (strlen(direc) + 1));
	if (!d)
	{
		free(command);
		perror("Malloc Fail");
		exit(EXIT_FAILURE);
	}
	strcpy(d, direc);
	free(direc);
	token = strtok(d, ":");
	while (token)
	{
		token = _strcat(token, command);
		if (access(token, X_OK) == 0)
		{
			free(d);
			free(command);
			return (token);
		}
		free(token);
		token = strtok(NULL, ":");
	}
	free(command);
	free(d);
	token = "N_F";
	return (token);
}

		


