#include "shell.h"


/**
 * handlewhitespace - function to fix whitespace
 * @str: string in which whitespace is removed
 * Return: new fixed string without leading and trailing whitespace
*/
char *handlewhitespace(char *str)
{
	char *newstr;

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
