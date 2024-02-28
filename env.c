#include "shell.h"

/**
 * _azemyenv - printss the current environment
 * @inffo: Structure containing potential argumentss. Used to maintain
 *          constant function prototype.
 * Return: Alwayss 0
 */
int _azemyenv(info_t *inffo)
{
	azeprint_list_str(inffo->env);
	return (0);
}

/**
 * _azemysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inffo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _azemysetenv(info_t *inffo)
{
	if (inffo->argc != 3)
	{
		_azeeputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_azesetenv(inffo, inffo->argv[1], inffo->argv[2]))
		return (0);
	return (1);
}

/**
 * _azegetenv - gets the value of an environ variable
 * @ionfo: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_azegetenv(info_t *ionfo, const char *name)
{
	list_t *node = ionfo->env;
	char *p;

	while (node)
	{
		p = azestarts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _azemyunsetenv - Remove an environment variable
 * @iznfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _azemyunsetenv(info_t *iznfo)
{
	int i;

	if (iznfo->argc == 1)
	{
		_azeeputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= iznfo->argc; i++)
		_azeunsetenv(iznfo, iznfo->argv[i]);

	return (0);
}

/**
 * azepopulate_env_list - popullates env linked list
 * @iznfo: Structure containing potential argumennts. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int azepopulate_env_list(info_t *iznfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		azeadd_node_end(&node, environ[i], 0);
	iznfo->env = node;
	return (0);
}
