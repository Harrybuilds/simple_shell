#include "shell.h"

/**
 *processcommand - function to modify commands
 *@string: string to be modified
 *Return: a char pointer
*/
char *processcommand(char *string, char *path)
{
	char *fullpath;
	char *token;
	char *cpy;
	char *newstr;
	char *new_sub;

	newstr = handlewhitespace(string);

	if (strncmp(newstr, "/bin/", 5) == 0)
	{
		token = strtok(strdup(newstr), " ");
		printf("token: %s\n",token);
	        
		fullpath = get_full_path(token, path);
		printf("Full path: %s\n", fullpath);
		if (fullpath)
		{
/*			freepointer(new_sub);
			freepointer(fullpath);*/
			return (newstr);
		}
		else
		{
			errno = 2;
			freepointer(new_sub);
			return (fullpath);
		}
		
	}
	else
	{
		cpy = malloc(strlen(newstr) + 6);
		strcpy(cpy, "/bin/");
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
			freepointer(newstr);
			errno = 2;
			freepointer(cpy);
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

char *handlewhitespace(char *str) {
    if (str == NULL || *str == '\0') {
        return strdup("");  // Return an empty string if input is NULL or empty
    }

    const char *start = str;
    const char *end = str + strlen(str) - 1;

    // Trim leading whitespace
    while (isspace(*start)) {
        start++;
    }

    // Check if the string is all whitespace
    if (*start == '\0') {
        return strdup("");  // Return an empty string if the entire string is whitespace
    }

    // Trim trailing whitespace
    while (end > start && isspace(*end)) {
        end--;
    }

    // Calculate the length of the trimmed substring
    size_t length = end - start + 1;

    // Allocate memory for the trimmed substring
    char *trimmed_str = (char *)malloc(length + 1); // +1 for the null-terminator
    if (trimmed_str == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Copy the trimmed substring to the new memory location
    strncpy(trimmed_str, start, length);
    trimmed_str[length] = '\0'; // Null-terminate the string

    return (trimmed_str);
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

