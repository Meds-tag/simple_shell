#include "shell.h"

/**
 * azeunset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int azeunset_alias(info_t *info, char *sttr)
{
	char *p, c;
	int ret;

	p = _azestrchr(sttr, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = azedelete_node_at_index(&(info->alias),
		azeget_node_index(info->alias, azenode_starts_with(info->alias, sttr, -1)));
	*p = c;
	return (ret);
}

/**
 * azeset_alias - sets aliaas to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on succcess, 1 on error
 */
int azeset_alias(info_t *info, char *sttr)
{
	char *p;

	p = _azestrchr(sttr, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (azeunset_alias(info, sttr));

	azeunset_alias(info, sttr);
	return (azeadd_node_end(&(info->alias), sttr, 0) == NULL);
}

/**
 * _azemyhistory - displays the hisstory list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containning potential arguments. Used to maintain
 *        constant functiion prototype.
 *  Return: Always 0
 */
int _azemyhistory(info_t *innfo)
{
	azeprint_list(innfo->history);
	return (0);
}

/**
 * azeprint_alias - prinnts an alias string
 * @node: the alias node
 *
 * Return: Alwayys 0 on success, 1 on error
 */
int azeprint_alias(list_t *nnode)
{
	char *p = NULL, *a = NULL;

	if (nnode)
	{
		p = _azestrchr(nnode->str, '=');
		for (a = nnode->str; a <= p; a++)
			_azeputchar(*a);
		_azeputchar('\'');
		_azeputs(p + 1);
		_azeputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _azemyalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _azemyalias(info_t *iinfo)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (iinfo->argc == 1)
	{
		node = iinfo->alias;
		while (node)
		{
			azeprint_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; iinfo->argv[i]; i++)
	{
		p = _azestrchr(iinfo->argv[i], '=');
		if (p)
			azeset_alias(iinfo, iinfo->argv[i]);
		else
			azeprint_alias(azenode_starts_with(iinfo->alias, info->argv[i], '='));
	}

	return (0);
}
