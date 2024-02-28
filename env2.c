#include "shell.h"

/**
 * azeget_environ - returns the strinng array copy of our environ
 * @info: Structure containing potential argumeints. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **azeget_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = azelist_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _azesetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var propperty
 * @value: the string env var value
 *  Return: Alwayys 0
 */
int _azesetenv(info_t *info, char *var, char *value)
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
	node = info->env;
	while (node)
	{
		p = azestarts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	azeadd_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * _azeunsetenv - Remove  an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant  function prototype.
 *  Return: 1 on d elete, 0 otherwise
 * @var: the string env var propertyy
 */
int _azeunsetenv(info_t *info, char *var)
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
			info->env_changed = azedelete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
