#include "shell.h"

/**
 * azeadd_node - adds a node to the start of the list
 * @ead: address of pointer to ead node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *azeadd_node(list_t **ead, const char *str, int num)
{
	list_t *new_ead;

	if (!ead)
		return (NULL);
	new_ead = malloc(sizeof(list_t));
	if (!new_ead)
		return (NULL);
	_azememset((void *)new_ead, 0, sizeof(list_t));
	new_ead->num = num;
	if (str)
	{
		new_ead->str = _azestrdup(str);
		if (!new_ead->str)
		{
			free(new_ead);
			return (NULL);
		}
	}
	new_ead->next = *ead;
	*ead = new_ead;
	return (new_ead);
}

/**
 * azeadd_node_end - adds a node to the end of the list
 * @ead: address of pointer to ead node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *azeadd_node_end(list_t **ead, const char *str, int num)
{
	list_t *new_node, *node;

	if (!ead)
		return (NULL);

	node = *ead;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_azememset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _azestrdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*ead = new_node;
	return (new_node);
}

/**
 * azeprint_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t azeprint_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_azeputs(h->str ? h->str : "(nil)");
		_azeputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * azedelete_node_at_index - deletes node at given index
 * @ead: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int azedelete_node_at_index(list_t **ead, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!ead || !*ead)
		return (0);

	if (!index)
	{
		node = *ead;
		*ead = (*ead)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *ead;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * azefree_list - frees all nodes of a list
 * @ead_ptr: address of pointer to ead node
 *
 * Return: void
 */
void azefree_list(list_t **ead_ptr)
{
	list_t *node, *next_node, *ead;

	if (!ead_ptr || !*ead_ptr)
		return;
	ead = *ead_ptr;
	node = ead;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ead_ptr = NULL;
}
