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
/**
 * _fork - function
 * @path: string
 * @buf: string
 * @commands: double pointer
 * @status: pointer
 */
void _fork(char *path, char *buf, char **commands, int *status)
{
	pid_t child;

	child = fork();
	if (child == -1)
		free(path), free(buf), perror("Fork failed"), exit(EXIT_FAILURE);
	else if (child == 0)
	{
		*status = execve(path, commands, environ);
		if (*status == -1)
			free(path), free(buf), perror("we found error"), exit(0);
	}
	else
	{
		if (wait(status) == -1)
			free(path), free(buf), perror("wait has failed"), exit(0);
		*status = WEXITSTATUS(*status);
	}

}
/**
 * main - entry
 * Return: Always 0
 */
int main(void)
{
	char *buf, *token, *commands[100], *trimmed, *path;
	size_t count, i;
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
