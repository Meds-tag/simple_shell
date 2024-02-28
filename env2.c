#include "shell.h"

/**
 * azeget_environ - returns the strinng array copy of our environ
 * @iznfo: Structure containing potential argumeints. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **azeget_environ(info_t *iznfo)
{
	if (!iznfo->environ || iznfo->env_changed)
	{
		iznfo->environ = azelist_to_strings(iznfo->env);
		iznfo->env_changed = 0;
	}

	return (iznfo->environ);
}

/**
 * _azesetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @iznfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var propperty
 * @value: the string env var value
 *  Return: Alwayys 0
 */
int _azesetenv(info_t *iznfo, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_azestrlen(var) + _azestrlen(value) + 2);
	if (!buf)
		return (1);
	_azestrcpy(buf, var);
	_azestrcat(buf, "=");
	_azestrcat(buf, value);
	node = iznfo->env;
	while (node)
	{
		p = azestarts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			iznfo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	azeadd_node_end(&(iznfo->env), buf, 0);
	free(buf);
	iznfo->env_changed = 1;
	return (0);
}

/**
 * _azeunsetenv - Remove  an environment variable
 * @iznfo: Structure containing potential arguments. Used to maintain
 *        constant  function prototype.
 *  Return: 1 on d elete, 0 otherwise
 * @var: the string env var propertyy
 */
int _azeunsetenv(info_t *iznfo, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = azestarts_with(node->str, var);
		if (p && *p == '=')
		{
			iznfo->env_changed = azedelete_node_at_index(&(iznfo->env), i);
			i = 0;
			node = iznfo->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (iznfo->env_changed);
}
