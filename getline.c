#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * custom_getline - Reads a line of input from the user.
 * Return: Pointer to the input line.
 */
char *custom_getline(void)
{
    static char buffer[BUFFER_SIZE];
    static size_t buffer_index = 0; 
    static ssize_t bytes_read = 0; 
    char *line = NULL;
    size_t line_size = 0;
    size_t max_line_size = BUFFER_SIZE;  

    line = malloc(max_line_size);
    if (line == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        /*  If there are no more bytes in the buffer, read from stdin */
        if (buffer_index == 0 || bytes_read == 0)
        {
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);

            if (bytes_read == -1)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            /* If we reach the end of input (EOF), return NULL */
            if (bytes_read == 0)
            {
                if (line != NULL && line_size > 0)
                    return line; 
                else
                    return NULL; 
            }

            buffer_index = 0; 
        }

        /*  Check for newline character in the buffer */
        while (buffer_index < (size_t)bytes_read && buffer[buffer_index] != '\n')
        {
            /*  Check if the line buffer needs to be resized */
            if (line_size >= max_line_size - 1)
            {
                fprintf(stderr, "Line too long. Increase BUFFER_SIZE.\n");
                exit(EXIT_FAILURE);
            }

                line[line_size++] = buffer[buffer_index++];
        }

        
	if (buffer_index < (size_t)bytes_read && buffer[buffer_index] == '\n')
        {
           
            if (line_size < max_line_size - 1)
                line[line_size++] = '\n';

            line[line_size] = '\0';  
            buffer_index++;          
	    return line;
        }
    }
}

int main(void)
{
    char *input = NULL;

    while (1)
    {
        display_prompt();

        input = custom_getline();

        if (input == NULL)
        {
            exit(EXIT_SUCCESS);
        }

        
        handlecommandline(char *string, int count);

        free(input);
    }

    return 0; 
}

