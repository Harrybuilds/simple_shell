#ifndef SHELL_H
#define SHELL_H

/**** MACROS ****/
#define MAX_INPUT_SIZE 1024
#define MAX_ARGUMENT 32
#define BUFFER_SIZE 1024

/* STANDARD LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>

void display_prompt(void);
void handlecommandline(char *string, int count);
void freepointer(char *ptr);
void execute_command(char *command, int count);
void parentprocess(pid_t pid, int status, char *command);
char *processcommand(char *string, char *path);
char **tokenizestr(char *str, char *delim);
void free_2dbuffer(char **args);
char *handlewhitespace(char *str);
char *get_full_path(const char *command, const char *path);
char *parsepath(char *path_copy, char *input_command);
void freepointer(char *ptr);
char *extract_substring(const char *str);
char *custom_getline(void);

#endif /* SHELL_H */
