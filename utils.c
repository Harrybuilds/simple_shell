#include "shell.h"

/**
 *processcommand - function to modify commands
 *@string: string to be modified
 *@path: path to search for command
 *Return: a char pointer
*/
char *processcommand(char *string, char *path)
{
	char *fullpath, *token, *cpy;
	char *newstr, newsub;

	newstr = handlewhitespace(string);
	if (strncmp(newstr, "/bin/", 5) == 0)
	{
		token = strtok(strdup(newstr), " ");
		new_sub = extract_substring(token);
		fullpath = get_full_path(new_sub, path);
		if (token == fullpath)
		{
			freepointer(new_sub);
			freepointer(fullpath);
			return (newstr);
		}
		else
		{
			errno = 2;
			return (fullpath);
		}
	}
	else
	{
		cpy = malloc(strlen(newstr) + 6);
		strcpy(cpy, "/bin/");
		strcat(cpy, "/");
		strcat(cpy, newstr);
		token = strtok(strdup(cpy), " ");
		fullpath = get_full_path(newstr, path);
		if (token == fullpath)
		{
			free(fullpath);
			return (cpy);
		}
		else
		{
			errno = 2;
			return (fullpath);
		}
	}
}




/**
 * tokenizestr - function to parse a string into 2d array
 * @str: string to be parsed
 * @delim: delimeter to be used for parsing the string
 * Return: a 2d array pointer pointing to the parsed string
*/

char **tokenizestr(char *str, char *delim)
{
	char **argv;
	int index = 0;
	char *token;

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
 *free_2dbuffer - free the 2d array holding all parts of command
 *@args: 2d array holding the tokenized commands
 *
 *Return: no value is returned
 */


/* Function to free the memory allocated for parsed command arguments*/
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


