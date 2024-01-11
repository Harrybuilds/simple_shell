#ifndef SHELL_H
#define SHELL_H

/**** MACROS ****/
#define MAX_INPUT_SIZE 1024
#define MAX_ARGUMENT 32
extern char **environ;

/* STANDARD LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>



int interractive(void);
int non_interractive(void);
int handlecommandline(char *command, int count, char *paths);
void prompt(char *promp);
int executecommand(char *command, int count, char *paths);
int validatecommand(char *command, char *paths);
int handle_execution(char **argv);
int commandreport(char *command, char *paths);
int checkpath(char *command, char *paths);
char **tokenizer(char *str, char *delim);
char *extract_substring(char *str);
int processcommand(char *string, char *paths);
char *handlewhitespace(char *str);
void free_2dbuffer(char **args);
void freepointer(char *ptr);
char *prefixcommand(char *command);
char *getpath(char **env);

#endif /* SHELL_H */
