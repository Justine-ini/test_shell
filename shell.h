#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void prompt(char **av, char **env);
char *_getenv(const char *name, char **env);
char *search_in_path(const char *command, const char *path);
int find_command(const char *command, char **env, char *command_path);
char *build_path(char *dir, char *command);
void print_message(void);

#endif
