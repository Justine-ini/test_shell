#include "shell.h"

#define NUM_CMD 8

/**
 * prompt - Displays a prompt and executes user commands
 * @av: The array of command-line arguments
 * @env: The array of environment variables
 * This function continuously prompts the user for commands and executes them
 * It displays the prompt 'commandme$ ' and reads the user input from stdin
 * The input is stored in the 'input' variable, and each command is executed
 * by forking a child process and using execve to run the command
 * If the command is not found, an error message is displayed
 * Return: None
 */

void prompt(char **av, char **env)
{
	char *input = NULL;
	pid_t pid;
	char *argv[NUM_CMD];
	size_t input_size = 0;
	int status, i, j;
	ssize_t characters_read;


	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(1, "commandme$ ", 12);
		}
		characters_read = getline(&input, &input_size, stdin);
		if (characters_read == -1)
		{
			free(input);
			exit(EXIT_FAILURE);
		}
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '\n')
			{
				input[i] = 0;
			}
		}
		j = 0;
		argv[j] = strtok(input, " ");
		for (; argv[j]; j++)
		{
			argv[j + 1] = strtok(NULL, " ");
		}
		pid = fork();
		if (pid == -1)
		{
			free(input);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				write(1, av[0], sizeof(av[0]) - 1);
				write(1, ": No such file or directory\n", 28);
			}
		}
		else
		{
			wait(&status);
		}
	}
}
