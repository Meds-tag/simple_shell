#include "shell.h"

/**
 * hsh - main shell loop
 * @nfo: the parameter & return info struct
 * @iav: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *nfo, char **iav)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		azeclear_info(nfo);
		if (azeinteractive(info))
			_azeputs("$ ");
		_azeeputchar(BUF_FLUSH);
		r = azeget_input(nfo);
		if (r != -1)
		{
			azeset_info(nfo, iav);
			builtin_ret = azefind_builtin(nfo);
			if (builtin_ret == -1)
				azefind_cmd(nfo);
		}
		else if (azeinteractive(nfo))
			_azeputchar('\n');
		azefree_info(nfo, 0);
	}
	azewrite_history(nfo);
	azefree_info(nfo, 1);
	if (!azeinteractive(nfo) && nfo->status)
		exit(nfo->status);
	if (builtin_ret == -2)
	{
		if (nfo->err_num == -1)
			exit(nfo->status);
		exit(nfo->err_num);
	}
	return (builtin_ret);
}

/**
 * azefind_cmd - finds a command in PATH
 * @nfo: the parameter & return info struct
 *
 * Return: void
 */
void azefind_cmd(info_t *nfo)
{
	char *path = NULL;
	int i, k;

	nfo->path = nfo->argv[0];
	if (nfo->linecount_flag == 1)
	{
		nfo->line_count++;
		nfo->linecount_flag = 0;
	}
	for (i = 0, k = 0; nfo->arg[i]; i++)
		if (!azeis_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = azefind_path(nfo, _azegetenv(info, "PATH="), nfo->argv[0]);
	if (path)
	{
		nfo->path = path;
		azefork_cmd(nfo);
	}
	else
	{
		if ((azeinteractive(nfo) || _azegetenv(nfo, "PATH=")
			|| nfo->argv[0][0] == '/') && azeis_cmd(nfo, nfo->argv[0]))
			azefork_cmd(nfo);
		else if (*(nfo->arg) != '\n')
		{
			nfo->status = 127;
			azeprint_error(nfo, "not found\n");
		}
	}
}

/**
 * azefind_builtin - finds a builtin command
 * @innfo: the parameter & return info struct
 *
 * Return: -1 if built in not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int azefind_builtin(info_t *innfo)
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
		if (_azestrcmp(innfo->argv[0], builtintbl[i].type) == 0)
		{
			innfo->line_count++;
			built_in_ret = builtintbl[i].func(innfo);
			break;
		}
	return (built_in_ret);
}


/**
 * azefork_cmd - forks a an exec thread to run cmd
 * @nfo: the parameter & return info struct
 *
 * Return: void
 */
void azefork_cmd(info_t *nfo)
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
		if (execve(nfo->path, nfo->argv, azeget_environ(nfo)) == -1)
		{
			azefree_info(nfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(nfo->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(nfo->status);
			if (nfo->status == 126)
				azeprint_error(nfo, "Permission denied\n");
		}
	}
}
