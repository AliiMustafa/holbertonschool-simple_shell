#include "main.h"
/**
 * print_env - func for printing rnv
 */
void print_env(void)
{
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
	}
}
/**
 * built_in_exit - function
 * @commands: double pointer
 * @buf: string
 * @status: pointer
 */
void built_in_exit(char **commands, char *buf, int *status)
{
	if (strcmp(commands[0], "exit") == 0)
	{
		free(buf);
		if (*status != 2)
			exit(0);
		exit(*status);
	}
}
