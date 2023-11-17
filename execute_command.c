#include "shell.h"
#include <unistd.h>

/**
 * execute_command - Execute a command based on the information in ShellInfo structure
 * @info: Pointer to ShellInfo structure
 */
void execute_command(ShellInfo *info)
{
	const char *message =
		"Command executed successfully!\n";

	execve(info->program_name, info->args, NULL);
	{
		perror("execve");
	}
	write(STDOUT_FILENO, message, strlen(message));
}

