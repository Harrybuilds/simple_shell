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

void display_prompt(void);
void handlecommandline(char *string);
char *processcommand(char *string);
void freepointer(char *ptr);
void execute_command(char *command);
char *handlewhitespace(char *str);

#endif /* SHELL_H */

