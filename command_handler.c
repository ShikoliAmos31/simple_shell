#include "command_handler.h"

/**
 * command_handler - Handle command lines with arguments
 * @ac: the command line
 * @av: the argument vector
 * Return: 0
 */
int command_handler(int ac, char **av)
{
	if (ac < 2)
	{
		char error_msg[] = "Usage: <command> [arguments...]\n";

		write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
		return (1);
	}

	/* Forking and executing the command */
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		char fork_error[] = "fork error\n";

		write(STDERR_FILENO, fork_error, sizeof(fork_error) - 1);
		return (1);
	}
	if (child_pid == 0)
	{
		/* Child process */
		char **args = &av[1];

		if (execve(args[0], args) == -1)
		{
			char exec_error[] = "execve error\n";

			write(STDERR_FILENO, exec_error, sizeof(exec_error) - 1);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);

		/* Handling child process status */
		if (WIFEXITED(status))
		{
			char status_msg[50];
			int len = snprintf(status_msg, sizeof(status_msg),
					"Child process exited with status %d\n", WEXITSTATUS(status));

			write(STDOUT_FILENO, status_msg, len);
		}
		else if (WIFSIGNALED(status))
		{
			char signal_msg[40];
			int len = snprintf(signal_msg, sizeof(signal_msg),
					"Child process terminated by signal %d\n", WTERMSIG(status));

			write(STDOUT_FILENO, signal_msg, len);
		}
	}
	return (0);
}
