#include "shell.h"
#include <unistd.h>
/**
 * cleanup_shell_info - Clean up resources associated with ShellInfo structure
 * @info: Pointer to ShellInfo structure
 */
void cleanup_shell_info(ShellInfo *info)
{
	int i;

	/* Free dynamically allocated memory */
	free(info->program_name);
	free(info->alias);
	free(info->user_input);

	/* Free args, assuming it's an array of strings ending with NULL */
	if (info->args != NULL)
	{
		for (i = 0; info->args[i] != NULL; ++i)
		{
			free(info->args[i]);
		}
		free(info->args);
	}
	/* Close file descriptors if they are valid */
	if (info->file_descriptor != -1)
	{
		close(info->file_descriptor);
	}
	if (info->out_fd != -1)
	{
		close(info->out_fd);
	}
}

