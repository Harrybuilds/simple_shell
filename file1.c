#include "shell.h"

/**
 * main - program execution
 * @void: nothing is expected as argument
 * Return: the status of tge command called
 */
int main(void)
{
	char *command = NULL;
	size_t commandsize = 0;
	int count = 0;
	int com_stat = 0;

	while (1)
	{
		printf("($) ");
		if (getline(&command, &commandsize, stdin) == -1)
		{
			if (command)
			{
				freepointer(command);
			}
			exit(com_stat);
		}
		command[strcspn(command, "\n")] = '\0';
		count++;

		com_stat = handlecommandline(command, count);
	}

	freepointer(command);
	return (com_stat);
}


/**
 * handlecommandline - function to takecare of multiple commands
 * @command: command to be handled
 * @count: count of commands passed
 * Return: integer represent command stat
*/
int handlecommandline(char *command, int count)
{
	char *argv[MAX_INPUT_SIZE];
	int index = 0;
	char *delim = ";&&";
	char *token = NULL;
	int com_stat = 0;

	if (strcmp(command, "exit") == 0)
	{
		if (command)
		{
			freepointer(command);
		}
		exit(EXIT_SUCCESS);
	}

	token = strtok(command, delim);

	while (token != NULL)
	{
		argv[index] = strdup(token);
		index += 1;
		token = strtok(NULL, delim);
	}
	argv[index] = NULL;

	index = 0;
	while (argv[index] != NULL)
	{
		com_stat = executecommand(argv[index], count);
		freepointer(argv[index]);
		index += 1;
		printf("command status: %d\n", com_stat);
		return (com_stat);
	}
	return (com_stat);
}


/**
 * executecommand - function to begin command execution
 * @command: command to be executed
 * @count: count of commands passed
 * Return: integer value representing command execution state
*/
int executecommand(char *command, int count)
{
	char **argv = NULL;
	int com_stat = 0;

	argv = tokenizer(command, " ");

	com_stat = validatecommand(argv[0]);

	if (com_stat == 1)
	{
		com_stat = handle_execution(argv);
		/*set the desired return value*/
	}
	else
	{
		/*report command isnt valid*/
		/*"\nFork cannot be called\n")*/
		fprintf(stderr, "./hsh: %s: %d cannot be found", command, count);

		/*set the desired return value*/
		errno = 127;
		com_stat = 127;
	}
	free_2dbuffer(argv);
	return (com_stat);
}


/**
 *validatecommand - function to verify command
 * @command: command to be verified
 * Return: integer value that represent the command state
*/
int validatecommand(char *command)
{
	int com_status = 0;

	if (!command || strlen(command) == 0)
	{
		return (-1);
	}

	com_status = commandreport(command);

	return (com_status);
}


/**
 * commandreport - function to call other function that validates command
 * @command: command to be validated
 * Return: integer value representing command state
*/
int commandreport(char *command)
{
	char *newstr = NULL;
	int returval = 0;

	newstr = handlewhitespace(command);
	returval = processcommand(newstr);

	/**
	 *POSSIBLE OUTCOME | ERRORS | POSSIBILlTIES
	 *command is not a valid command
	 *command is a valid command
	 *
	 *ASSIGNED STATUS OF OUTCOMES
	 *
	 *0 - command is valid and exist
	 *1 - command is not valid
	 *
	 **/

	return (returval);
}
