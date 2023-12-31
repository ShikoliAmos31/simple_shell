#include "shell.h"

/**
 * display_prompt - Display the shell prompt and execute commands
 * @prompt: Prompt to be displayed
 * @info: Poiner to ShellInfo
 */

void display_prompt(char *prompt, ShellInfo *info)
{
	int error_code;
	int input_length;

	while (1)
	{
		write(STDOUT_FILENO, prompt, strlen(prompt));
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
