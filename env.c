#include "shell.h"

/**
 * _azemyenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _azemyenv(info_t *info)
{
	azeprint_list_str(info->env);
	return (0);
}

/**
 * _azegetenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_azegetenv(info_t *info, const char *name)
{
	list_t *node = info->env;
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
 * _azemysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _azemysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_azeeputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_azesetenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _azemyunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _azemyunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_azeeputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_azeunsetenv(info, info->argv[i]);

	return (0);
}

/**
 * azepopulate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int azepopulate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		azeadd_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
