#include "shell.h"

/**
 * main - program  execution starts here
 * @void: nothing is expected as argument
 * Return: status of command execution
 *
*/
int main(void)
{
	int com_stat = 0;

	if (isatty(STDOUT_FILENO) == 1)
	{
		com_stat = interractive();
	}
	else
	{
		com_stat = non_interractive();
	}
	return (com_stat);
}
