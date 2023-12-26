#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */

void display_prompt(void)
{
    printf("($) ");
    fflush(stdout);
}

/**
 * execute_command - Executes the given command
 */
void execute_command(char *command)
{
    if (strcmp(command, "exit") == 0)
    {
        printf("Exiting the shell.\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */

           char *args[2];
            args[0] = command;
            args[1] = NULL;

            if (execve(command, args, NULL) == -1)
            {
                perror(command);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */

            int status;
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            {
                fprintf(stderr, "./hsh: %s: command not found\n", command);
            }
            else if (WIFSIGNALED(status))
            {
                fprintf(stderr, "./hsh: %s: terminated by signal %d\n", command, WTERMSIG(status));
            }
        }
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

    while (1)
    {
        display_prompt();

        if (getline(&input, &input_size, stdin) == -1)
        {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        execute_command(input);
    }

    free(input);

    return 0;
}

