#include "shell.h"
/**
 * main - my own getline function
 * Return: 0 always
 */
int main(void)
{
	char line[MAX_LINE_SIZE];
	char prompt[] = "You entered: ";
	char newline = '\n';

	while (1)
	{
		read_line(line, MAX_LINE_SIZE);

		if (line[0] == '\0')
		{
			continue;
		}
		write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
		write(STDOUT_FILENO, line, strlen(line));
		write(STDOUT_FILENO, &newline, 1);
	}
	return (0);
}
/**
 * read_line - function that reads the line
 * @line: buffer to store the line
 * @size: size of the buffer
 */
void read_line(char *line, size_t size)
{
	static char buffer[MAX_LINE_SIZE];
	static ssize_t buffer_index;
	static ssize_t chars_read;

	size_t line_length = 0;
	char current_char;

	while (1)
	{
		if (buffer_index >= chars_read)
		{
			chars_read = read(STDIN_FILENO, buffer, MAX_LINE_SIZE);
			if (chars_read == -1)
			{
				perror("Error reading input");
				exit(EXIT_FAILURE);
			}
			if (chars_read == 0)
			{
				/* End of input, return the line if any */
				line[line_length] = '\0';
				return;
			}
			buffer_index = 0;
		}
		current_char = buffer[buffer_index++];

		if (current_char == '\n' || current_char == '\0')
		{
			/* End of line, return the line */
			line[line_length] = '\0';
			return;
		}
		else
		{
			if (line_length < size - 1)
			{
				line[line_length++] = current_char;
			}
		}
	}
}
