#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to concatenate two strings
char *_strcat(char *str1, char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t total_len = len1 + len2;
    char *result = malloc(total_len + 1);
    if (result == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

// Function to handle the PATH environment variable and find the executable
char *handle_path(char *command) {
    char *direc, *token, *d;
    char *path_with_command;
    
    if (access(command, X_OK) == 0) {
        return command;
    }

    // Prepend '/' to command
    char *full_command = _strcat("/", command);
    if (full_command == NULL) {
        perror("Failed to concatenate path");
        exit(EXIT_FAILURE);
    }

    // Get PATH environment variable
    direc = getenv("PATH");
    if (direc == NULL) {
        free(full_command);
        perror("Failed to get PATH environment variable");
        exit(EXIT_FAILURE);
    }

    // Create a modifiable copy of PATH
    d = malloc(strlen(direc) + 1);
    if (d == NULL) {
        free(full_command);
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(d, direc);

    // Tokenize PATH and search for the executable
    token = strtok(d, ":");
    while (token) {
        path_with_command = _strcat(token, full_command);
        if (path_with_command == NULL) {
            free(d);
            free(full_command);
            perror("Failed to concatenate path");
            exit(EXIT_FAILURE);
        }
        if (access(path_with_command, X_OK) == 0) {
            free(d);
            free(full_command);
            return path_with_command;
        }
        free(path_with_command);
        token = strtok(NULL, ":");
    }

    free(d);
    free(full_command);
    return "N_F";
}
char *trim(char *string)
{
        char *cpy;
        int count = 0, i = 0, j = 0;
        while (string[j])
                j++;
        cpy = malloc(sizeof(char) * (j + 1));
        if (cpy == NULL)
                return (NULL);
        while (string[i])
        {
                cpy[i] = string[i];
                i++;
        }
        cpy[i] = '\0';
        for (i = 0; cpy[i] != '\0'; i++)
        {
                if (cpy[i] != ' ')
                {
                        cpy[count] = cpy[i];
                        count++;
                }
        }
        cpy[count] = '\0';
        return (cpy);
}

int main(void) 
{
    char *buf, *token, *commands[100], *trimmed, *path;
    size_t count = 0;
    pid_t child;
    int status, i;

    while (1) 
    {
	    buf = NULL, i = 0;
        if (getline(&buf, &count, stdin) == -1) {
            free(buf);
            exit(0);
        }

        trimmed = trim(buf);
        if (trimmed[0] == '\n') {
            free(trimmed);
            continue;
        }
        free(trimmed);
        token = strtok(buf, " \n");
        while (token) {
            commands[i] = token;
            token = strtok(NULL, " \n");
	    i++;
        }
        commands[i] = NULL;

        path = handle_path(commands[0]);
        if (strcmp(path, "N_F") == 0) {
            free(buf);
            continue;
        }

        child = fork();
        if (child == -1) 
	{
            perror("Fork failed");
            free(buf);
            exit(EXIT_FAILURE);
        } 
	else if (child == 0) 
	{
            if (execve(path, commands, NULL) == -1) 
	    {
                perror("Execve failed");
                free(buf);
                exit(EXIT_FAILURE);
            }
        } 
	else 
	{
            if (wait(&status) == -1) 
	    {
                perror("Wait failed");
                free(buf);
                exit(EXIT_FAILURE);
            }
        }

        free(buf);
    }

    return 0;
}

