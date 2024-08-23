#ifndef MAIN_H
#define MAIN_H

#includ <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
extern char **environ;
void print_env(void);
char *trim(char *string);
char *handle_path(char *command);
char *get_env(char *path);
#endif
