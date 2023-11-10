#include "shell.h"

/**
* env_built_in - implement the environment
* @env: the current environment
* Return: 0 always
*/
int env_built_in(char **env)
{
	int i;
	size_t len;

	for (i = 0; env[i] != NULL; i++)
	{
		len = 0;
		while (env[i][len] != '\0')
		{
			len++;
		}
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

