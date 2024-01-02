#include "shell.h"

/**
 * execute_command_path - Executes the given command with PATH handling
 * @command: command to be executed
 * Return: nothing is returned
 */
/**char *execute_command_path(char *command)
{
	char *token;
	int rv;

	/* Get the PATH before forking 
	char *path = getenv("PATH");
	char *full_path;
    
	/* Check if the command is available 
	token = strtok(path, ":");
	while (token != NULL)
	{
	    /* Construct the full path *
		full_path = malloc(strlen(token) + strlen(command) + 2); /* +2 for '/' and '\0' *
		if (full_path == NULL)
		{
			perror("error allocating space");
			exit(EXIT_FAILURE);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

/*	printf("FULL PATH B4 validate: %s\n ", full_path);*
        /* Check if the file exists *
		rv = access(full_path, F_OK);
		printf("rv : %d\npath : %s\n", rv, full_path);
		if (rv == 0)
		{
			/* If the command is found, set the flag and break the loop *
			printf("Valid command:%s\n", full_path);
			return strdup(full_path);
		}

		/* Clean up and move to the next directory in PATH *
		free(full_path);
		token = strtok(NULL, ":");
	}
	return (NULL);

    /* If the command is not found or is not readable, print an error and exit 
    if (!command_found)
    {
        fprintf(stderr, "./hsh: %s: command not found or not readable\n", argv[0]);
        freepointer(exec_command);
        exit(EXIT_FAILURE);
	}*


}*/

char *execute_command_path(const char *command) {
    if (command == NULL || strlen(command) == 0) {
        fprintf(stderr, "Invalid command\n");
        return NULL;
    }

    // Get the PATH before forking
    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not found\n");
        return NULL;
    }

    char *token = strtok(path, ":");
    while (token != NULL) {
        // Construct the full path
        char *full_path = malloc(strlen(token) + strlen(command) + 2); // +2 for '/' and '\0'
        if (full_path == NULL) {
            perror("Error allocating space");
            exit(EXIT_FAILURE);
        }
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);

        // Check if the file exists
        if (access(full_path, F_OK) == 0) {
            printf("Valid command: %s\n", full_path);
            return full_path;
        }

        // Clean up and move to the next directory in PATH
        free(full_path);
        token = strtok(NULL, ":");
    }

    fprintf(stderr, "Command '%s' not found\n", command);
    return NULL;
}


int main ()
{
	char *input;
	char *path;
	size_t input_size;
	
	while (1)
	{
		printf("$ ");
		if (getline(&input, &input_size, stdin) == -1)
		{
			exit(EXIT_SUCCESS);
		}
	

		path = execute_command_path(input);

		if (path)
		{
			printf("%s\n", path);
		}
		else if(path == NULL)
			printf("path is NULL");
	}
}
