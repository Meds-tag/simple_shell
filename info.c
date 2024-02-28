#include "shell.h"

/**
 * azeset_info - initializes info_t struct
 * @nnfo: struct address
 * @av: argument vector
 */
void azeset_info(info_t *nnfo, char **av)
{
	int i = 0;

	nnfo->fname = av[0];
	if (nnfo->arg)
	{
		nnfo->argv = azestrtow(nnfo->arg, " \t");
		if (!nnfo->argv)
		{

			nnfo->argv = malloc(sizeof(char *) * 2);
			if (nnfo->argv)
			{
				nnfo->argv[0] = _azestrdup(nnfo->arg);
				nnfo->argv[1] = NULL;
			}
		}
		for (i = 0; nnfo->argv && nnfo->argv[i]; i++)
			;
		nnfo->argc = i;

		azereplace_alias(nnfo);
		azereplace_vars(nnfo);
	}
}


/**
 * azeclear_info - initializes info_t struct
 * @nfo: struct address
 */
void azeclear_info(info_t *nfo)
{
	nfo->arg = NULL;
	nfo->argv = NULL;
	nfo->path = NULL;
	nfo->argc = 0;
}


/**
 * azefree_info - frees info_t struct fields
 * @winfo: struct address
 * @all: true if freeing all fields
 */
void azefree_info(info_t *winfo, int all)
{
	azeffree(winfo->argv);
	winfo->argv = NULL;
	winfo->path = NULL;
	if (all)
	{
		if (!winfo->cmd_buf)
			free(winfo->arg);
		if (winfo->env)
			azefree_list(&(winfo->env));
		if (winfo->history)
			azefree_list(&(winfo->history));
		if (winfo->alias)
			azefree_list(&(winfo->alias));
		azeffree(winfo->environ);
			winfo->environ = NULL;
		azebfree((void **)winfo->cmd_buf);
		if (winfo->readfd > 2)
			close(winfo->readfd);
		_azeputchar(BUF_FLUSH);
	}
}
