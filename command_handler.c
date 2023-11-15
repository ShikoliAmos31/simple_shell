#include "shell.h"

/**
 * handle_child_process_status - Handle the status of the child process
 * @status: The status of the child process
 */
static void handle_child_process_status(int status)
{
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

/**
 * run_child_process - Run the logic for the child process
 * @command: The command to execute
 */
static void run_child_process(char **command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		write(STDERR_FILENO, "fork error\n", strlen("fork error\n"));
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		/* Child process */
		if (execve(command[0], command, NULL) == -1)
		{
			write(STDERR_FILENO, "execve error\n", strlen("execve error\n"));
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		wait(&status);
		handle_child_process_status(status);
	}
}

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
		write(STDERR_FILENO, "Usage: <command> [arguments...]\n",
				strlen("Usage: <command> [arguments...]\n"));
		return (1);
	}
	/* Extracting command and arguments */
	char **command = &av[1];

	/* Forking and executing the command */
	run_child_process(command);
	return (0);
}
