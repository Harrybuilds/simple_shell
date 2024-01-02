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
 * @count: count of commands entered
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
 * @count: count of command passed
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


/**
 * checkpath - function to verify command
 * @command: command to be verified
 * @count: count of command passed
 * Return: an integer that represent command status
 */
int checkpath(char *command)
{
	char *paths = NULL;
	char *path_cpy = NULL;
	char *token = NULL;
	int status = 0;
	char *fullpath = NULL;

	paths = getenv("PATH");
	path_cpy = strdup(paths);

	token = strtok(path_cpy, ":");
	while (token != NULL)
	{
		fullpath = malloc(strlen(token) + strlen(command) + 2);
		strcpy(fullpath, token);
		strcat(fullpath, "/");
		strcat(fullpath, command);

		if (access(fullpath, F_OK) == 0)
		{
			status = 1;
			freepointer(fullpath);
			break;
		}
		else
		{
			/*not a valid command*/
			status = 0;
		}
		freepointer(fullpath);
		token = strtok(NULL, ":");
	}
	freepointer(path_cpy);
	return (status);
}


/**
 * processcommand - function to cleanup the command
 * @string: command to be cleaned up
 * @count: count of command passed
 * Return: an integer value representing where command is valid or not
 */
int processcommand(char *string)
{
	int com_stat = 0;
	char *token = NULL;
	char *new_sub = NULL;

	if (strncmp(string, "/bin/", 5) == 0)
	{
		token = strtok(string, " ");
		new_sub = extract_substring(token);
		com_stat = checkpath(new_sub);
		freepointer(new_sub);
		return (com_stat);
	}
	else
	{
		token = strtok(string, " ");
		com_stat = checkpath(token);

		return (com_stat);
	}
}



/**
 * handlewhitespace - function to fix whitespace
 * @str: string in which whitespace is removed
 * Return: new fixed string without leading and trailing whitespace
*/
char *handlewhitespace(char *str)
{
	char *newstr = NULL;

	/*trim leading whitespace*/
	while (isspace(*str))
		str++;

	if (*str == 0)
		return (str);

	/*trim trailling whitespace*/
	newstr = str + strlen(str) - 1;
	while (newstr > str && isspace(*newstr))
		newstr--;

	newstr[1] = '\0';

	return (str);
}


/**
 *freepointer - function to free dynamic allocated space
 *@ptr: character pointer to be freed
 *return: nothing is returned
*/
void freepointer(char *ptr)
{
	free(ptr);
}


/**
 * extract_substring - to remove "/bin/" from command if needed
 * @str: command to be operated on
 * Return: the command with the "/bin/" prefixing it
*/
char *extract_substring(char *str)
{
	const char *prefix = "/bin/";
	size_t prefix_len = strlen(prefix);

	/* Check if the string starts with the prefix "/bin/"*/
	if (strncmp(str, prefix, prefix_len) == 0)
	{
		/* Return the substring after the prefix "/bin/"*/
		return (strdup(str + prefix_len));
	}

	/* If the prefix is not found, return NULL or an appropriate message*/
	return (str);
}


/**
 *tokenizer - function to parse a command based of a given delimeter
 * @str: command to be parsed
 * @delim: delimeter to be used for parsing command
 * Return: 2d array formed as a result of parsing command
*/
char **tokenizer(char *str, char *delim)
{
	char **argv;
	int index = 0;
	char *token = NULL;

	argv = malloc(MAX_ARGUMENT * sizeof(char *));
	if (argv == NULL)
	{
		perror("failure to allocate memory");
		exit(EXIT_FAILURE);
	}

	token = strtok(str, delim);
	while (token != NULL && index < MAX_ARGUMENT - 1)
	{
		argv[index] = strdup(token);
		index += 1;
		token = strtok(NULL, delim);
	}
	argv[index] = NULL;

	return (argv);
}


/**
 * free_2dbuffer - function to free 2d array
 * @args: 2d array to be freed
 * Return: nothing is returned
 */

void free_2dbuffer(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}


/**
 * handle_execution - function to execute commands
 * @argv: 2d array holding body of command
 * @count: number of commands entered
 * Return: integer representing command stat
*/
int handle_execution(char **argv)
{
	int status = 0;
	pid_t pid;
	char *command = NULL;

	command = prefixcommand(argv[0]);
	pid = fork();

	if (pid == -1)
	{
		perror("fork call failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command, argv, NULL);
		/*if execve reaches here, execve failed*/
		/*errno holds the specific code and message*/
		if (command)
			freepointer(command);
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}
	else
	{
		if (command)
			freepointer(command);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
			return (WEXITSTATUS(status));
		}
		else
		{
			printf("Child process terminated abnormally\n");
			return (11);
		}
	}
}


/**
 *prefixcommand - function to prefix "/bin/" to command if needed
 * @command: command to be prefixed if needed
 * Return: the command starting with "/bin/"
*/
char *prefixcommand(char *command)
{
	char *copy = NULL;

	if (strncmp(command, "/bin/", 5) != 0)
	{
		copy = malloc(strlen(command) + 6);
		if (copy == NULL)
		{
			perror("Error allocating space");
		}
		strcpy(copy, "/bin/");
		strcat(copy, command);
		return (copy);
	}
	return (strdup(command));
}



/**
 *POSSIBLE OUTCOME | ERRORS | POSSIBILlTIES
 *command is NULL or EMPTY
 *path is NULL
 *command is not a valid command
 *command is a valid command
 */

/**
 *ASSIGNED STATUS OF OUTCOMES
 *0 - command is valid and exist
 *-1 - command is empty
 *1 - command is not valid
 **/

/**
 *TODO
 *verify command is not NULL
 *verify path is not NULL
 */

/**
 *call function that takes command, cleanup whitespaces in the command, then process the command to remove prefix '/bin/' if any, then return the leftover characters in the command
 *
 *tokenize the first part of a copy of the returned leftover characters with space
 *
 *call a function that takes the token returned from tokenizing the command copy as argument, then verify if the command exist, then return an integer based on the outcome of verification
 *
 *if integer return says command exits,then call on fork system call
 *
 *handle both child and parent process
 */
