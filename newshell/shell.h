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



int handlecommandline(char *command, int count);
int executecommand(char *command, int count);
int validatecommand(char *command);
int handle_execution(char **argv);
int commandreport(char *command);
int checkpath(char *command);
char **tokenizer(char *str, char *delim);
char *extract_substring(char *str);
int processcommand(char *string);
char *handlewhitespace(char *str);
void free_2dbuffer(char **args);
void freepointer(char *ptr);
char *prefixcommand(char *command);


#endif /* SHELL_H */

