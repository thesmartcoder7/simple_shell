#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @data: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_pool *data)
{
	int (*builtin)(data_pool *data);

	if (data->args[0] == NULL)
		return (1);

	builtin = get_builtin(data->args[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (cmd_exec(data));
}
