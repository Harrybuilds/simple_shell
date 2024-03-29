#include "shell.h"

/**
 * checkpath - function to verify command
 * @command: command to be verified
 * @paths: environment variable path
 * Return: an integer that represent command status
 */
int checkpath(char *command, char *paths)
{
	char *path_cpy = NULL;
	char *token = NULL;
	int status = 0;
	char *fullpath = NULL;

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
 * @paths: environment variable path
 * Return: an integer value representing where command is valid or not
 */
int processcommand(char *string, char *paths)
{
	int com_stat = 0;
	char *token = NULL;
	char *new_sub = NULL;

	if (strncmp(string, "/bin/", 5) == 0)
	{
		token = strtok(string, " ");
		new_sub = extract_substring(token);
		com_stat = checkpath(new_sub, paths);
		freepointer(new_sub);
		return (com_stat);
	}
	else
	{
		token = strtok(string, " ");
		com_stat = checkpath(token, paths);

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
