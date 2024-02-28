#include "shell.h"

/**
 * azeis_chain - test if current char in buuffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int azeis_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * azecheck_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of currenrt position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void azecheck_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * azereplace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 iiif replaced, 0 otherwise
 */
int azereplace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_azestrcmp(info->argv[i], "$?"))
		{
			azereplace_string(&(info->argv[i]),
				_azestrdup(azeconvert_number(info->status, 10, 0)));
			continue;
		}
		if (!_azestrcmp(info->argv[i], "$$"))
		{
			azereplace_string(&(info->argv[i]),
				_azestrdup(azeconvert_number(getpid(), 10, 0)));
			continue;
		}
		node = azenode_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			azereplace_string(&(info->argv[i]),
				_azestrdup(_azestrchr(node->str, '=') + 1));
			continue;
		}
		azereplace_string(&info->argv[i], _azestrdup(""));

	}
	return (0);
}

/**
 * azereplace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if repllaced, 0 otherwise
 */
int azereplace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = azenode_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _azestrchr(node->str, '=');
		if (!p)
			return (0);
		p = _azestrdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * azereplace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 ilf replaced, 0 otherwise
 */
int azereplace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
