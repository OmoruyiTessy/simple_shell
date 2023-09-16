#include "shell.h"

/**
 * execute_command - Execute a command
 * @command: The command to execute
 *
 * Return: The exit status of the executed command
 */
int execute_command(char *command)
{
	pid_t child_pid;
	int status;

	char *args[MAX_INPUT_SIZE];
	int arg_count = 0;

	split_command(command, args, &arg_count);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, WUNTRACED);
		if (WIFEXITED(status))
		{
			last_exit_status = WEXITSTATUS(status);
		}
	}

	return (last_exit_status);
}
