#include "shell.h"

/**
 * display_prompt - Display the shell prompt and execute commands
 * @prompt: Prompt to be displayed
 * @info: Poiner to ShellInfo
 */

void display_prompt(char *prompt, ShellInfo *info)
{
	print_to_console(prompt);

	while (1)
	{
		print_to_console(prompt);
		error_code = input_length = get_user_input(info);

		if (error_code == EOF)
		{
			cleanup_shell_info(info);
			exit(0);
		}
		if (input_length >= 1)
		{
			execute_command(info);
		}
	}
}
