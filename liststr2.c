#include "shell.h"

/**
 * azelist_len - determines length of linked list
 * @r: pointer to first node
 *
 * Return: size of list
 */
size_t azelist_len(const list_t *r)
{
	size_t i = 0;

	while (r)
	{
		r = r->next;
		i++;
	}
	return (i);
}

/**
 * azelist_to_strings - returns an array of strings of the list->str
 * @sead: pointer to first node
 *
 * Return: array of strings
 */
char **azelist_to_strings(list_t *sead)
{
	list_t *node = sead;
	size_t i = azelist_len(sead), j;
	char **strs;
	char *str;

	if (!sead || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_azestrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _azestrcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * azeprint_list - prints all elements of a list_t linked list
 * @e: pointer to first node
 *
 * Return: size of list
 */
size_t azeprint_list(const list_t *e)
{
	size_t i = 0;

	while (e)
	{
		_azeputs(azeconvert_number(e->num, 10, 0));
		_azeputchar(':');
		_azeputchar(' ');
		_azeputs(e->str ? e->str : "(nil)");
		_azeputs("\n");
		e = e->next;
		i++;
	}
	return (i);
}

/**
 * azeget_node_index - gets the index of a node
 * @sead: pointer to list sead
 * @nnode: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t azeget_node_index(list_t *sead, list_t *nnode)
{
	size_t i = 0;

	while (sead)
	{
		if (sead == nnode)
			return (i);
		sead = sead->next;
		i++;
	}
	return (-1);
}


/**
 * azenode_starts_with - returns node whose string starts with suffux
 * @nnode: pointer to list sead
 * @suffux: string to match
 * @c: the next character after suffux to match
 *
 * Return: match nnode or null
 */
list_t *azenode_starts_with(list_t *nnode, char *suffux, char c)
{
	char *p = NULL;

	while (nnode)
	{
		p = azestarts_with(nnode->str, suffux);
		if (p && ((c == -1) || (*p == c)))
			return (nnode);
		nnode = nnode->next;
	}
	return (NULL);
}
