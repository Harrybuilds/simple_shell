#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 * Return: nothing is returned
 */

void display_prompt(void)
{
	printf("($) ");
}

/**
 * execute_command - Executes the given command
 * @command: command to be executed
 * Return: nothing is returned
 */
void execute_command(char *command)
{
	char *argv[MAX_ARGUMENT];
	char *token;
	int index = 0, status;
	pid_t pid;
	char *exec_command;

	if (strcmp(command, "exit") == 0)
	{
		printf("Exiting the shell.\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		/**parse the command using whitespace*/
		exec_command = processcommand(command);

		token = strtok(exec_command, " ");
		while (token != NULL)
		{
			argv[index] = token;
			index += 1;
			token = strtok(NULL, " ");
		}
		argv[index] = NULL;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* child  process */
			if (execve(argv[0], argv, NULL) == -1)
			{
				fprintf(stderr, "./hsh: %s: %s\n", command, strerror(errno));
				exit(errno);
			}
		}
		else
		{
			freepointer(exec_command);
			/* Parent process */

			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				fprintf(stderr, "./hsh: %s: %s\n", command, strerror(errno));
			}
			else if (WIFSIGNALED(status))
			{
				fprintf(stderr, "./hsh: %s: terminated by signal %d\n", command, WTERMSIG(status));
			}
		}
	}
}


/**
 * main - Entry point for the simple shell program
 * Return: Always 0 on success
 */

int main(void)
{
	char *input = NULL;
	size_t input_size = 0;

	while (1)
	{
		display_prompt();

		if (getline(&input, &input_size, stdin) == -1)
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';
		handlecommandline(input);

	}
	freepointer(input);

	return (0);
}

/**
 *handlecommandline - function to parse multiple commands
 *@string: commands passed as strings
 *return: no value is returned
*/
void handlecommandline(char *string)
{

	char *argv[10];
	size_t index = 0;
	char *delim = ";&&";
	char *token;

	token = strtok(string, delim);


	while (token != NULL)
	{
		argv[index] = token;
		index += 1;
		token = strtok(NULL, delim);
	}
	argv[index] = NULL;

	index = 0;
	while (argv[index] != NULL)
	{
		execute_command(argv[index]);
		index += 1;
	}
}

/**
 *processcommand - function to modify commands
 *@string: string to be modified
 *Return: a char pointer
*/
char *processcommand(char *string)
{
	char *cpy;
	int lenOriginal = strlen(string);
	char *newstr;

	newstr = handlewhitespace(string);
	if (strncmp(newstr, "/bin/", 5) == 0)
	{
		return (strdup(newstr));
	}
	else
	{
		cpy = malloc(lenOriginal + 6);

	if (cpy == NULL)
	{
		perror("error allocating space");
		exit(EXIT_FAILURE);
	}

	strcpy(cpy, "/bin/");
	strcat(cpy, newstr);

	return (cpy);
	}
}
