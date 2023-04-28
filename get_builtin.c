#include "shell.h"

/**
 * get_builtin - builtin that parse the command in the arg
 * @ss_cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *ss_cmd))(data_pool *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, ss_cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
