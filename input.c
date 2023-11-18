#include "shell.h"
/**
 * get_user_input -  Get iser input from te console
 * @info: Pointer to ShellInfo structure
 * Return: Length of user input
 */

int get_user_input(ShellInfo *info)
{
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	info->user_input =  malloc(MAX_INPUT_SIZE);

	if (!info->user_input)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (fgets(info->user_input, MAX_INPUT_SIZE, stdin) == NULL)
	{
		free(info->user_input);
		return (EOF);
	}

	info->user_input[strcspn(info->user_input, "\n")] = '\0';

	return (strlen(info->user_input));
}
