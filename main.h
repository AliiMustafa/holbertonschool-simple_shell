#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
extern char **environ;
void _fork(char *path, char *buf, char **commands, int *status);
void built_in_exit(char **commands, char *buf, int *status);
void print_env(void);
char *trim(char *string);
char *handle_path(char *command);
char *get_env(char *path);
#endif
