#include "shell.h"

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

