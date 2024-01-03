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
 * @count: number of times a command has be passed to this program per session
 * Return: nothing is returned
 */
void execute_command(char *command, int count)
{
	char **argv;
	int status=0;
	pid_t pid;
	char *exec_command;
	char *path;

	if (strcmp(command, "exit") == 0)
	{
		if (command)
		{
			freepointer(command);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		path = getenv("PATH");
		/*parse the command using whitespace*/
		exec_command = processcommand(command, path);
		if (exec_command != NULL)
		{
			argv = tokenizestr(exec_command, " ");
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
					fprintf(stderr, "%s: %d: %s: %s\n", argv[0], count, command, "not found");
					exit(errno);
				}
			}
			else
			{
			freepointer(exec_command);
			free_2dbuffer(argv);
			/* Parent process */
			parentprocess(pid, status, "./hsh");
			}

		}
		else
		{
			fprintf(stderr, "%s cannot be found\n", command);
			/*return a status code*/
		}
	}
}

/**
 *parentprocess - function to handle parent process
 *@pid: pid of the process
 *@status: status returned
 *@command: command passed
 *Return: nothing is returned
 **/

void parentprocess(pid_t pid, int status, char *command)
{
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		fprintf(stderr, "./hsh: %s: %s\nstatus: %d, errno: %d\n", command, strerror(errno), status, errno);
	}
	else if (WIFSIGNALED(status))
	{
		fprintf(stderr, "./hsh: %s: terminated by signal %d\nstatus: %d errno: %d\n", command, WTERMSIG(status), status, errno);
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
	int count = 0;

	while (1)
	{
		display_prompt();

		if (getline(&input, &input_size, stdin) == -1)
		{
			if (input)
			{
				freepointer(input);
			}
			exit(EXIT_SUCCESS);
		}

		input[strcspn(input, "\n")] = '\0';
		count++;
		handlecommandline(input, count);

	}
	freepointer(input);

	return (0);
}

/**
 *handlecommandline - function to parse multiple commands
 *@string: commands passed as strings
 *@count: coun5 passed from the calling function
 *return: no value is returned
*/
void handlecommandline(char *string, int count)
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
		execute_command(argv[index], count);
		index += 1;
	}
}
