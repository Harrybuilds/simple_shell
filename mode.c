#include "shell.h"

/**
 * interractive - handle program execution in interactive mode
 * @void: nothing is expected as argument
 * Return: the status of tge command called
 */
int interractive(void)
{
	char *command = NULL;
	size_t commandsize = 0;
	int count = 0;
	int com_stat = 0;
	char *paths = getenv("PATH") ? getenv("PATH") : "/bin/";

	while (1)
	{
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

		com_stat = handlecommandline(command, count, paths);
	}

	freepointer(command);
	return (com_stat);
}




/**
 * non_interractive - function to be executed non-interaction mode
 * @void: no argument expected
 * Return: status of command execution
 *
*/
int non_interractive(void)
{
	char buffer[MAX_INPUT_SIZE];
	ssize_t bytes;
	int count = 0;
	int com_stat = 0;
	char *paths = getenv("PATH") ? getenv("PATH") : "/bin/";


	/* Read input from the terminal*/
	bytes = read(STDIN_FILENO, buffer, sizeof(buffer));

	if (bytes == -1)
	{
		perror("Error reading from terminal");
		return (1);
	}
	buffer[bytes] = '\0';

	count++;

	com_stat = handlecommandline(buffer, count, paths);

	return (com_stat);
}



/**
 * prompt - function to print prompt
 * @promp: string to be printed as prompt
 * Return: nothing is returned
*/
void prompt(char *promp)
{
	printf("%s ", promp);
}




