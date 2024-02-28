#include "shell.h"

/**
 * _azemyhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _azemyhistory(info_t *info)
{
	azeprint_list(info->history);
	return (0);
}

/**
 * azeunset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int azeunset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _azestrchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = azedelete_node_at_index(&(info->alias),
		azeget_node_index(info->alias, azenode_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * azeset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int azeset_alias(info_t *info, char *str)
{
	char *p;

	p = _azestrchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (azeunset_alias(info, str));

	azeunset_alias(info, str);
	return (azeadd_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * azeprint_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int azeprint_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _azestrchr(node->str, '=');
		for (a = node->str; a <= p; a++)
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
int _azemyalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			azeprint_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _azestrchr(info->argv[i], '=');
		if (p)
			azeset_alias(info, info->argv[i]);
		else
			azeprint_alias(azenode_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
