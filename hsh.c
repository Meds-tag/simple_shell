#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		azeclear_info(info);
		if (azeinteractive(info))
			_azeputs("$ ");
		_azeeputchar(BUF_FLUSH);
		r = azeget_input(info);
		if (r != -1)
		{
			azeset_info(info, av);
			builtin_ret = azefind_builtin(info);
			if (builtin_ret == -1)
				azefind_cmd(info);
		}
		else if (azeinteractive(info))
			_azeputchar('\n');
		azefree_info(info, 0);
	}
	azewrite_history(info);
	azefree_info(info, 1);
	if (!azeinteractive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * azefind_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int azefind_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _azemyexit},
		{"env", _azemyenv},
		{"help", _azemyhelp},
		{"history", _azemyhistory},
		{"setenv", _azemysetenv},
		{"unsetenv", _azemyunsetenv},
		{"cd", _azemycd},
		{"alias", _azemyalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_azestrcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * azefind_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void azefind_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!azeis_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = azefind_path(info, _azegetenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		azefork_cmd(info);
	}
	else
	{
		if ((azeinteractive(info) || _azegetenv(info, "PATH=")
			|| info->argv[0][0] == '/') && azeis_cmd(info, info->argv[0]))
			azefork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			azeprint_error(info, "not found\n");
		}
	}
}

/**
 * azefork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void azefork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, azeget_environ(info)) == -1)
		{
			azefree_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				azeprint_error(info, "Permission denied\n");
		}
	}
}
