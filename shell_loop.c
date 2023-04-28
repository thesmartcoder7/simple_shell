#include "shell.h"

/**
 * without_comment - delete comments from the input
 *
 * @input: input string
 * Return: input without comments
 */

char *without_comment(char *input)
{
	int i, term;

	term = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				term = i;
		}
	}

	if (term != 0)
	{
		input = _realloc(input, i, term + 1);
		input[term] = '\0';
	}

	return (input);
}

/**
 * shell_loop - Loop of shell
 * @data: data relevant (av, input, args)
 * Return: no return.
 */

void shell_loop(data_pool *data)
{
	int loop, mk_eof, length;
	char *input, *prompt;

	prompt = _strcat(getlogin(), "@shell$ ");
	length = _strlen(_strcat(getlogin(), "@shell$ "));
	loop = 1;

	while (loop == 1)
	{
		write(STDOUT_FILENO, prompt, length);
		input = read_line(&mk_eof);
		if (mk_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(data, input) == 1)
			{
				data->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, data);
			loop = split_commands(data, input);
			data->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
