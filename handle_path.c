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
	char *direc, *token, *d, *c, *command1, *temp;

	if (access(command, X_OK) == 0)
	{
		c = malloc(sizeof(char) * (strlen(command) + 1));
		strcpy(c, command);
		return (c);
	}
	command1 = _strcat("/", command);
	if (!command1)
	{
		perror("Failed to concat");
		exit(EXIT_FAILURE);
	}
	direc = get_env("PATH");
	if (!direc || strcmp(direc, "(null)") == 0)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		free(command1);
		exit(127);
	}
	d = malloc(sizeof(char) * (strlen(direc) + 1));
	if (!d)
	{
		free(command1);
		free(direc);
		perror("Malloc Fail");
		exit(EXIT_FAILURE);
	}
	strcpy(d, direc);
	free(direc);
	token = strtok(d, ":");
	while (token)
	{
		temp = _strcat(token, command1);
		if (access(temp, X_OK) == 0)
		{
			free(d);
			free(command1);
			return (temp);
		}
		free(temp);
		token = strtok(NULL, ":");
	}
	free(command1);
	free(d);
	return ("N_F");
}
