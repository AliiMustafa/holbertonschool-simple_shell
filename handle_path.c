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
	char *direc, *token, *d;

	if (access(command, X_OK) == 0)
		return (command);
	command = _strcat("/", command);
	if (!command)
	{
		free(command);
		perror("Failed to concat");
		exit(EXIT_FAILURE);
	}
	direc = getenv("PATH");
	d = malloc(sizeof(char) * (strlen(direc) + 1));
	if (!d)
	{
		free(command);
		perror("Malloc Fail");
		exit(EXIT_FAILURE);
	}
	strcpy(d, direc);
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
		token = strtok(NULL, ":");
	}
	free(d);
	token = "N_F";
	return (token);
}

		


