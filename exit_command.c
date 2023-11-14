#include "shell.h"
/**
 * exit_command - Implement the exit built-in, that exits the shell
 *
 */
void exit_command(void)
{
	const char exit_message[] = "Exiting the shell.\n";
	const size_t exit_message_len = sizeof(exit_message) - 1;

	write(1, exit_message, exit_message_len);

	_exit(EXIT_SUCCESS);
}
