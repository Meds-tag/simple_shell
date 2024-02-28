#include "shell.h"

/**
 * azeclear_info - initializes info_t struct
 * @info: struct address
 */
void azeclear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * azeset_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void azeset_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = azestrtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _azestrdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		azereplace_alias(info);
		azereplace_vars(info);
	}
}

/**
 * azefree_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void azefree_info(info_t *info, int all)
{
	azeffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			azefree_list(&(info->env));
		if (info->history)
			azefree_list(&(info->history));
		if (info->alias)
			azefree_list(&(info->alias));
		azeffree(info->environ);
			info->environ = NULL;
		azebfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_azeputchar(BUF_FLUSH);
	}
}
