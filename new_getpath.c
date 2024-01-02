#include "shell.h"


/**
 * get_full_path - function to attempt getting the full path of a command
 *@command: the command to attempt verifing it's fullpath
 *@path: path to used for the verification process
 * Return: fullpath of command if valid else NULL
*/
char *get_full_path(const char *command, const char *path)
{
	char *input_command;
	char *full_path;
	char *path_copy;

	if (command == NULL || strlen(command) == 0)
	{
		fprintf(stderr, "Invalid command\n");
		return (NULL);
	}
	if (path == NULL || strlen(path) == 0)
	{
		fprintf(stderr, "PATH environment variable not found\n");
		return (NULL);
	}
	input_command = extract_substring(command);
	printf("Searching for command: %s\n", command);
	printf("Current PATH: %s\n", path);
	/* Duplicate the command string for manipulation*/
	/*input_command = strdup(command);*/
	if (input_command == NULL)
	{
		perror("Error duplicating command");
		exit(EXIT_FAILURE);
	}
	/* Make a copy of PATH for tokenizing*/
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("Error duplicating PATH");
		exit(EXIT_FAILURE);
	}

	full_path = parsepath(path_copy, input_command);

	freepointer(input_command);
	freepointer(path_copy);
	return (full_path);
}

/**
 * parsepath - focuses on tokenizing the path and validating the path
 *@path_copy: a copy of the path to be used for verification
 *@input_command: a copy of the command passed
 * Return: a valid fullpath or NULL
*/
char *parsepath(char *path_copy, char *input_command)
{
	char *token;
	char *full_path;
	int full_path_len;

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		/* Construct the full path*/
		full_path_len = strlen(token) + strlen(input_command) + 2;
		full_path = malloc(full_path_len); /* Allocate memory for full path*/
		if (full_path == NULL)
		{
			perror("Error allocating space");
			exit(EXIT_FAILURE);
		}
		snprintf(full_path, full_path_len, "%s/%s", token, input_command);
		printf("Checking path: %s\n", full_path);
		/* Check if the file exists*/
		if (access(full_path, F_OK) == 0)
		{
			return (full_path);
		}
		/* Clean up and move to the next directory in PATH*/
		free(full_path);
		token = strtok(NULL, ":");
	}
	freepointer(input_command);
	freepointer(path_copy);
	return (NULL);
}

char *extract_substring(const char *str)
{
    const char *prefix = "/bin/";
    size_t prefix_len = strlen(prefix);

    // Check if the string starts with the prefix "/bin/"
    if (strncmp(str, prefix, prefix_len) == 0) {
        // Return the substring after the prefix "/bin/"
        return strdup(str + prefix_len);
    }

    // If the prefix is not found, return NULL or an appropriate message
    return NULL;
}
