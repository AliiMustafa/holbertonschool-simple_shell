#include "main.h"
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
