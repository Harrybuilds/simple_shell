#ifndef SHELL_H
#define SHELL_H

/**** MACROS ****/
#define MAX_INPUT_SIZE 1024
#define MAX_ARGUMENT 32


/* STANDARD LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>

char *parsepath(char *path_copy, char *input_command);
char *get_full_path(const char *command, const char *path);
char *extract_substring(const char *str);
void display_prompt(void);
void handlecommandline(char *string, int count);
char *processcommand(char *string, char *path);
void freepointer(char *ptr);
void execute_command(char *command, int count);
char *handlewhitespace(char *str);
char **tokenizestr(char *str, char *delim);
void free_2dbuffer(char **args);
void parentprocess(pid_t pid, int status, char *executable_name);

#endif /* SHELL_H */

